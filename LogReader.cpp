/*************************************************************************
	       LogReader  -  Reads and parses an Apache Log 
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
					      Jules BRISARD
					      Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Réalisation de la classe <LogReader> (fichier LogReader.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "LogReader.h"
#include "LogEntry.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type LogReader::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

LogEntry LogReader::readLine(){
    string line;
    getline(logstream, line);
    istringstream iss(line);
    LogEntry log;
    string ignore;

    iss >> log.client_ip >> ignore >> ignore >> log.date;

    return log;
}


//------------------------------------------------- Surcharge d'opérateurs
LogReader & LogReader::operator = ( const LogReader & unLogReader )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
LogReader::LogReader ( const LogReader & unLogReader )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <LogReader>" << endl;
#endif
} //----- Fin de LogReader (constructeur de copie)


LogReader::LogReader(std::string& file_path)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <LogReader>" << endl;
#endif
fstream logstream(file_path);
} //----- Fin de LogReader


LogReader::~LogReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <LogReader>" << endl;
#endif
} //----- Fin de ~LogReader


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
