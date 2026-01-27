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
using namespace std;
#include <iostream>
#include <map>

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

    while (!(log = logs->readLine()).client_ip.empty()) {
        // Flags
	if (exclude)
	{
	    if (log.document_type != "html")
		{
			continue;
	    }
	}
	if (hour != -1)
	{
	    if (log.hour < hour || log.hour > hour + 1)
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

    if (grapher != nullptr)
    {
	grapher->GenerateGraphFile(interactions);
    }

    multimap<int, string> stats = GetDocumentByHit();
    int documentCount = 0;
    for (multimap<int, string>::reverse_iterator itr = stats.rbegin(); itr != stats.rend() && documentCount < 10; ++itr)
    {
	cout << itr->second << " (" << itr->first << " hits)" << endl;
	++documentCount;
    }
} //----- Fin de Méthode

multimap<int, string> LogStats::GetDocumentByHit ( )
// Algorithme :
//
{
    multimap<int, string> docHits;
    for (const pair<string, int> & pair : hits) {
        docHits.insert(make_pair(pair.second, pair.first));
    }
    return docHits;
} //----- Fin de Méthode


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
