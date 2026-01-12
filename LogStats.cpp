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

//------------------------------------------------------ Include personnel
#include "LogStats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void LogStats::AnalyseLogs ( string filename, string graph = "", bool exclude = false, int hour = -1 )
// Algorithme :
//
{
    // Get logs from reader
    reader = LogReader.Load(filename);
    if (grapher != "")
	grapher.Setup(graph); // A changer
    while (reader) {
        // Flags
	if (exclude) {
	    if (reader.log.documentType == "js" || reader.log.documentType == "css" || reader.log.documentType == "png") {
		reader = reader.Next();
		continue;
	    }
	}
	if (hour != -1) {
	    if (reader.log.hour < hour*3600 || reader.log.hour > (hour + 1)*3600) {
		reader = reader.Next();
		continue;
	    }
	}

	if (interactions.find(reader.log.target) == interactions.end()) {
	    map<string, int> referrers;
	    interactions.insert({reader.log.target, referrers});
	}

	map<string, int> referrers = interactions.find(reader.log.target)->second;
	if (referrers.find(reader.log.referrer) == referrers.end()) {
	    referrers.insert({reader.log.referrer, 0});
	}
	referrers[reader.log.referrer] += 1;
	interactions[reader.log.target] = referrers;


	if (hits.find(reader.log.target) == hits.end()) {
	    hits.insert({reader.log.target, 0});
        }
	hits[reader.log.target] += 1;

	reader = reader.Next();
    }

    if (graph) {
	grapher.GenerateGraph(interactions);
    }

    multimap<int, string> stats = GetDocumentByHit();
    int documentCount = 0;
    for (multimap<int, string>::iterator itr = stats.end(); itr != stats.begin() && documentCount < 10; --itr) {
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
LogStats::LogStats ( const LogStats & unLogStats )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <LogStats>" << endl;
#endif
} //----- Fin de LogStats (constructeur de copie)


LogStats::LogStats ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <LogStats>" << endl;
#endif
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
