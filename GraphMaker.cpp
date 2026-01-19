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
//-------------------------------------------------------- Include système
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
GraphMaker::GraphMaker(const string& filename) :
outputGraphFilename(filename)
{
  outfile.open(outputGraphFilename);

  if(!outfile.is_open()){
    // error whilst creating the file
     cerr << "Error: Could not create the file " << outputGraphFilename << ".\n";
  }
}

GraphMaker::~GraphMaker(){
  // close the file if for some reason it wasn't done before yo!
  if(outfile.is_open()){
      outfile.close();
  }
}

//--------------------------------------------------------------- Methodes
void GraphMaker::generateGraphFile(const unordered_map<string, unordered_map<string, int> >& graph_umap){

  // double check to see if the thing is alright yo!
  if (!outfile.is_open()) {
    cerr << "Error: No file is open. can't create a .dot file from it" << endl;
    return;
  }
  //start
  outfile << "digraph {\n";

  for(const auto& pair: graph_umap){
    const string& targetNode = pair.first; // string (the one we go to)
    const auto& source_nodes= pair.second; // umap<int, string> referres (from where we come from to go to target)

    createNode(outfile, targetNode);

    // go through the nodes in the umap
    for(const auto& node: source_nodes){ //inverted

      const auto& sourceNode= node.first; // from who we call from
      const auto& weight = node.second;

      createLink(outfile, sourceNode, targetNode, weight);
    }
  }

  //end! yay
  outfile << "}\n";

  if(outfile.is_open()){
      outfile.close();
  }

  cout << "Dot-file" << outputGraphFilename << "generated yo!" << endl;

  return;

}

inline void GraphMaker::createNode(ofstream& of, const string& nodeName){
  of << " \"" << nodeName << "\";\n";
}

inline void GraphMaker::createLink(ofstream& of, const string& fromNode, const string& toNode, const long int occurences){
  of << " \"" << fromNode << "\" -> \"" << toNode << "\" [label=\"" << occurences << "\"];\n";
}
