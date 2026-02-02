/*************************************************************************
	       LogStats  -  Generates stats for Apache Logs 
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
					      Jules BRISARD
					      Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Réalisation de la classe <LogStats> (fichier LogStats.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <regex>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogStats.h"
#include "LogReader.h"
#include "GraphMaker.h"
#include "LogEntry.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void LogStats::AnalyseLogs ( GraphMaker *grapher, bool exclude, int hour)
// Algorithme :
//
{
    LogEntry log;

	if (hour != -1) {
        cout << "Attention : seulement les hits entre " << hour << "h et " << (hour + 1) % 24 
             << "h sont pris en compte." << endl;
    }

	if (exclude) {
		cout << "Les fichiers images, CSS et JS seront exclus de l'analyse." << endl;
	}

    while (!(log = logs->readLine(base_url)).client_ip.empty()) {
        // Flags
	if (exclude)
	{
	    if (file_extensions.find(log.document_type) != file_extensions.end())
		{
			continue;
	    }
	}
	if (hour != -1)
	{
	    if (log.hour < hour || log.hour >= hour + 1)
		{
			continue;
	    }
	}

	if (interactions.find(log.url) == interactions.end())
	{
	    unordered_map<string, int> referrers;
	    interactions.insert(pair<string, unordered_map<string, int>>(log.url, referrers));
	}

	unordered_map<string, int> referrers = interactions.find(log.url)->second;
	if (referrers.find(log.referer) == referrers.end())
	{
	    referrers.insert(pair<string, int>(log.referer, 0));
	}
	referrers[log.referer] += 1;
	interactions[log.url] = referrers;


	if (hits.find(log.url) == hits.end())
	{
	    hits.insert({log.url, 0});
    }
	hits[log.url] += 1;
    }

	if (hits.empty()) {
        cout << "Aucun résultat trouvé pour les critères demandés." << endl;
        return;
    }

	cout << "Classement des 10 documents les plus consultés :" << endl;

    multimap<int, string> stats = GetDocumentByHit();
    int documentCount = 0;
    for (multimap<int, string>::reverse_iterator itr = stats.rbegin(); itr != stats.rend() && documentCount < 10; ++itr)
    {
		cout << itr->second << " (" << itr->first << " hits)" << endl;
		++documentCount;
    }

	if (grapher != nullptr)
    {
		grapher->GenerateGraphFile(interactions);
		cout << "Fichier .dot généré avec succès." << endl;
    }
} //----- Fin de Méthode

multimap<int, string> LogStats::GetDocumentByHit ( )
// Algorithme :
//
{
    multimap<int, string> docHits;
    for (const pair<const string, int> & pair : hits) {
        docHits.insert(make_pair(pair.second, pair.first));
    }
    return docHits;
} //----- Fin de Méthode

void LogStats::loadConfig ()
// Algorithme :
//
{
    ifstream config_file;
    config_file.open("config.txt");
    string line;
    
    while (getline(config_file, line))
    {
	regex url_re("base_url(\\s*):(\\s*)(\\S+)");
	smatch match;
	if (regex_search(line, match, url_re) && match.size() > 1) {
	    base_url = match.str(3);
	}

	size_t ext_pos = line.find("file_ext");
	if (ext_pos != string::npos) {
		regex ext_re("\"([a-zA-Z0-9]+)\"");
	    sregex_iterator next(line.begin(), line.end(), ext_re);
	    sregex_iterator end;
	    while (next != end) {
		smatch match = *next;
		file_extensions.insert(match.str(1));
		next++;
	    }
	}
    }

    config_file.close();
}

//-------------------------------------------- Constructeurs - destructeur
LogStats::LogStats ( LogReader *reader )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <LogStats>" << endl;
#endif
    interactions = unordered_map<string, unordered_map<string, int>>();
    hits = unordered_map<string, int>();
    logs = reader;
    base_url = "";
    file_extensions = set<string>();
    loadConfig();
} //----- Fin de LogStats


LogStats::~LogStats ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <LogStats>" << endl;
#endif
} //----- Fin de ~LogStats


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
