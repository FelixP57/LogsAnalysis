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
// type LogStats::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
LogStats & LogStats::operator = ( const LogStats & unLogStats )
// Algorithme :
//
{
} //----- Fin de operator =


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
