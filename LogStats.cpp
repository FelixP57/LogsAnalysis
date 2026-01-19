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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void LogStats::AnalyseLogs ( GraphMaker *grapher = nullptr, bool exclude = false, int hour = -1 )
// Algorithme :
//
{
    while (logs) {
        // Flags
	if (exclude)
	{
	    if (logs.log.documentType == "js" || logs.log.documentType == "css" || logs.log.documentType == "png")
		{
			logs = logs.Next();
			continue;
	    }
	}
	if (hour != -1)
	{
	    if (logs.log.hour < hour*3600 || logs.log.hour > (hour + 1)*3600)
		{
			logs = logs.Next();
			continue;
	    }
	}

	if (interactions.find(logs.log.target) == interactions.end())
	{
	    unordered_map<string, int> referrers;
	    interactions.insert(pair<string, unordered_map<string, int>>(logs.log.target, referrers));
	}

	unordered_map<string, int> referrers = interactions.find(logs.log.target)->second;
	if (referrers.find(logs.log.referrer) == referrers.end())
	{
	    referrers.insert(pair<string, int>(logs.log.referrer, 0));
	}
	referrers[logs.log.referrer] += 1;
	interactions[logs.log.target] = referrers;


	if (hits.find(logs.log.target) == hits.end())
	{
	    hits.insert({logs.log.target, 0});
    }
	hits[logs.log.target] += 1;

	logs = logs.Next();
    }

    if (grapher != nullptr)
	{
		grapher->GenerateGraphFile(interactions);
    }

    multimap<int, string> stats = GetDocumentByHit();
    int documentCount = 0;
    for (multimap<int, string>::iterator itr = stats.end(); itr != stats.begin() && documentCount < 10; --itr)
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
LogStats::LogStats ( LogReader logReader )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <LogStats>" << endl;
#endif
    interactions = unordered_map<string, unordered_map<string, int>>();
    hits = unordered_map<string, int>();
    logs = logReader;
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
