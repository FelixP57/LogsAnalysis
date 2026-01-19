/*************************************************************************
	       LogStats  -  Generates stats for Apache Logs 
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
					      Jules BRISARD
					      Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Interface de la classe <LogStats> (fichier LogStats.h) ----------------
#if ! defined ( LOGSTATS_H )
#define LOGSTATS_H

//--------------------------------------------------- Interfaces utilisées
#include <unordered_map>
#include <map>
#include "LogReader.h"
#include "GraphMaker.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogStats>
//
//
//------------------------------------------------------------------------

class LogStats
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AnalyseLogs( GraphMaker *grapher = nullptr, bool exclude=false, int hour=-1 );
    // Mode d'emploi :
    //    Lit un fichier de logs, puis les analyse et renvoie les sites les plus consultés.
    //    Selon les flags, lance la génération d'un fichier ou exclut certains logs.
    // Contrat :
    //    hour est entre 0 et 23, graph est vide seulement si le flag n'est pas actif.

    multimap<int, string> GetDocumentByHit();
    // Mode d'emploi :
    //     Retourne une multimap avec en clé le nombre de hit et en clé les documents accédés.
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    LogStats ( LogReader logReader );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~LogStats ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    unordered_map<string, unordered_map<string, int>> interactions;
    unordered_map<string, int> hits;
    LogReader logs;
};

//-------------------------------- Autres définitions dépendantes de <LogStats>

#endif // LOGSTATS_H

