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
    LogEntry readLine();
    // Mode d'emploi : Lis la prochaine ligne du fichier associé au logstream
    // et renvoie le LogEntry associe
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    LogReader & operator = ( const LogReader & unLogReader );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    LogReader ( const LogReader & unLogReader );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    LogReader(std::string& file_path);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~LogReader ( );
    // Mode d'emploi :
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
    
