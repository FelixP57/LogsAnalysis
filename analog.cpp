#include <iostream>
#include <string>
#include <vector>

#include "LogStats.h"
#include "LogReader.h"
#include "GraphMaker.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    string logFileName = "";
    string dotFileName = "";
    bool excludeResources = false; 
    int selectedHour = -1;        
    bool generateGraph = false;  

    if (argc < 2) {
        cerr << "Utilisation: " << argv[0] << " [-g nomfichier.dot] [-e] [-t heure] nomfichier.log" << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-g" && i + 1 < argc) {
	    generateGraph = true;
	    dotFileName = argv[++i]; // L'argument suivant est le nom du fichier .dot
        } else if (arg == "-e") {
            excludeResources = true; // Exclure les fichiers images, css et javascript
        } else if (arg == "-t" && i + 1 < argc) {
            try {
                selectedHour = stoi(argv[++i]); // Intervalle [heure, heure+1[
	    } catch (...) {
                cerr << "Erreur: L'heure doit être un nombre entier." << endl;
                return 1;
            }
        } else {
            // Le dernier argument est le nom du fichier log
            logFileName = arg;
        }
    }

    if (logFileName.empty()) {
        cerr << "Erreur: Pas d'archive de logs spécifiée." << endl;
        return 1;
    }

    LogReader reader(logFileName);
    LogStats analyzer(&reader);

    if (generateGraph) {
	GraphMaker grapher(dotFileName);
	analyzer.AnalyseLogs(&grapher, excludeResources, selectedHour);
    } else {
	analyzer.AnalyseLogs(nullptr, excludeResources, selectedHour);
    }


    return 0;
}
