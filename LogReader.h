/*************************************************************************
	       LogReader  -  Reads and parses an Apache Log 
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
					      Jules BRISARD
					      Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Interface de la classe <LogReader> (fichier LogReader.h) ----------------
#ifndef LOGREADER_H
#define LOGREADER_H

#include <fstream>
#include <string>
#include "LogEntry.h"
using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogReader>
//
//
//------------------------------------------------------------------------

class LogReader
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    LogEntry readLine(string base_url);
    // Mode d'emploi : Lis la prochaine ligne du fichier associé au logstream
    // et renvoie le LogEntry associe
    //
    // Contrat : Le fichier doit être ouvert et valide

//-------------------------------------------- Constructeurs - destructeur
    LogReader ( const LogReader & unLogReader );
    // Mode d'emploi (constructeur de copie) : Renvoie juste un avertissement sur cout car copie inutile et dangereuse
    //
    // Contrat : Affiche un message d'avertissement à l'utilisateur

    LogReader(const string& file_path);
    // Mode d'emploi : Crée un LogReader et ouvre le fichier spécifié par file_path
    //
    // Contrat : Le fichier doit exister et être accessible en lecture

    virtual ~LogReader ( );
    // Mode d'emploi : Ferme le fichier
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    ifstream logstream;
};

//-------------------------------- Autres définitions dépendantes de <LogReader>

#endif // LOGREADER_H
    
