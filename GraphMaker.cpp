/*************************************************************************
                           GraphMaker  -  Générateur de graphe
                             -------------------
    début                : 2026-10-05
    copyright            : (C) 2026 par Raphael GUTEVILLE,
                                        Jules BRISARD,
                                        Gerald CHAMBI RAMOS
                                        Félix PIETRUCZANIS
*************************************************************************/

//---------- Réalisation de la classe <GraphMaker> (fichier GraphMaker.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "GraphMaker.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
GraphMaker & GraphMaker::operator = ( const GraphMaker & unGraphMaker )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
GraphMaker::GraphMaker ( const GraphMaker & unGraphMaker )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <GraphMaker>" << endl;
#endif
} //----- Fin de GraphMaker (constructeur de copie)


GraphMaker::GraphMaker ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <GraphMaker>" << endl;
#endif
} //----- Fin de GraphMaker


GraphMaker::~GraphMaker ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <GraphMaker>" << endl;
#endif
} //----- Fin de ~GraphMaker


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

