/*************************************************************************
                           GraphMaker  -  Générateur de graphe
                             -------------------
    début                : 2026-10-05
    copyright            : (C) 2026 par Raphael GUTEVILLE,
                                        Jules BRISARD,
                                        Gerald CHAMBI RAMOS
                                        Félix PIETRUCZANIS
*************************************************************************/

//---------- Interface de la classe <GraphMaker> (fichier GraphMaker.h) ----------------
#if ! defined ( GRAPHMAKER_H )
#define GRAPHMAKER_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Xxx>
//
//
//------------------------------------------------------------------------

class GraphMaker
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    GraphMaker & operator = ( const GraphMaker & unGraphMaker );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    GraphMaker ( const GraphMaker & unGraphMaker );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    GraphMaker ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~GraphMaker ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <GraphMaker>

#endif // GRAPHMAKER_H

