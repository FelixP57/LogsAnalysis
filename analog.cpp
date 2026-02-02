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

    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg == "-g")
        {
            if (i + 1 < argc)
            {
                generateGraph = true;
                string nomFichier = argv[i + 1];
                if (nomFichier[0] == '-' || nomFichier.length() < 4 || nomFichier.substr(nomFichier.length() - 4) != ".dot")
                {
                    cerr << "Erreur : L'option -g nécessite un nom de fichier .dot" << endl;
                    return 1;
                }
                dotFileName = argv[++i];
            }
            else
            {
                cerr << "Erreur : L'option -g nécessite un nom de fichier .dot" << endl;
                return 1;
            }
        }
        else if (arg == "-e")
        {
            excludeResources = true;
        }
        else if (arg == "-t")
        {
            if (i + 1 < argc)
            {
                try
                {
                    selectedHour = stoi(argv[++i]);
                    if (selectedHour < 0 || selectedHour > 23)
                    {
                        cerr << "Erreur : L'heure doit être comprise entre 0 et 23." << endl;
                        return 1;
                    }
                }
                catch (...)
                {
                    cerr << "Erreur : L'argument de -t doit être un entier." << endl;
                    return 1;
                }
            }
            else
            {
                cerr << "Erreur : L'option -t nécessite une heure." << endl;
                return 1;
            }
        }
        else
        {
            logFileName = arg;
        }
    }

    if (logFileName.empty())
    {
        cerr << "Erreur : Aucun fichier de log spécifié." << endl;
        return 1;
    }

    LogReader reader(logFileName);
    // Vérification de l'ouverture du fichier avant de continuer
    if (!reader.isOpen()) return 1;

    LogStats analyzer(&reader);
    GraphMaker* grapher = nullptr;

    if (generateGraph)
    {
        grapher = new GraphMaker(dotFileName);
    }

    analyzer.AnalyseLogs(grapher, excludeResources, selectedHour);

    if (grapher) delete grapher;

    return 0;
}