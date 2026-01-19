/*************************************************************************
	       GraphMaker  -  Creates the output graph of an already analyzed Apache Log
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
                                              Jules BRISARD
                                              Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Interface de la classe <GraphMaker> (fichier GraphMaker.h) ----------------
#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H


//--------------------------------------------------- Interfaces utilisées
// Include systeme
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;
// Include user
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GraphMaker>
//
//
//------------------------------------------------------------------------

class GraphMaker{

  public:
  //----------------------------------------------------- Méthodes publiques
  void GenerateGraphFile(const unordered_map<string, unordered_map<string, int>>& analyzed_umap);
  /* Generates a GraphViz .dot file for the corresponding graph deducted from analyze
   * Where each document (page) will apear under the form of a node et every 'link' indicates
   * the number of ocurrences associated.
   *
   * Returns: none but outputs to stderr depending if the creation of the file was succesful or not.
   */

  //-------------------------------------------- Constructeurs - destructeur
  GraphMaker( const string& filename );

  ~GraphMaker();

  //------------------------------------------------------------------ PRIVE
  private:
  //----------------------------------------------------- Méthodes protégées

    inline void createNode(ofstream& of, const string& nodeName);

    inline void createLink(ofstream& of, const string& fromNode, const string& toNode, const long int occurences);

  //----------------------------------------------------- Attributs protégés

    string outputGraphFilename;
    ofstream outfile;

};


#endif // fin de GRAPHMAKER_H
