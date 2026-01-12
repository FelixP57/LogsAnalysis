/*************************************************************************
	       GraphMaker  -  Reads and parses an Apache Log
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
					      Jules BRISARD
					      Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Réalisation de la classe <LogReader> (fichier LogReader.cpp) ------------

//---------------------------------------------------------------- INCLUDE

#include "GraphMaker.h"
#include "LogStats.h"
//-------------------------------------------------------- Include système
#include <fstream>
#include <iostream>

using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
GraphMaker::GraphMaker(const LogStats& stats, const string& filename) :
logStats(stats), outputGraphFilename(filename)
{
  outfile.open(outputGraphFilename);

  if(!outfile.is_open()){
      // error whilst creating the file
      cerr << "Error: Could not create the file " << outputGraphFilename << ".\n";
    }
}

GraphMaker::~GraphMaker(){

  if(outfile.is_open()){
    outfile.close();
  }
}

//--------------------------------------------------------------- Methodes
void GraphMaker::generateGraphFile(){


  //start
  outfile << "digraph {\n";

  // auto to now gaf about the type cuz im lazy
  const auto& graph_umap = logStats.getGraph(); // to change!

  for(auto& pair: graph_umap){
    const string& sourceNode = pair.first;
    const auto& target_nodes = pair.second;

    createNode(outfile, sourceNode);

    // go through the nodes in the umap
    for(const auto& node: target_nodes){
      const string& targetNode = node.first;
      long weight = node.second;

      createLink(outfile, sourceNode, targetNode, weight);
    }
  }

  //end
  outfile << "}\n";

  cout << "Dot-file" << outputGraphFilename << "generated." << endl;

  return;
}

inline void GraphMaker::createNode(ofstream& of, const string& nodeName){
  of << nodeName << ";\n";
}

inline void GraphMaker::createLink(ofstream& of, const string& fromNode, const string& toNode, const long int occurences){
  of << fromNode << " -> " << toNode << "[label="<< occurences<<"];\n";
}
