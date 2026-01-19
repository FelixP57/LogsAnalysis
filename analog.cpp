#include <iostream>
#include <string>
#include <vector>

#include "LogReader.h"
#include "LogStats.h"
#include "GraphMaker.h"

using namespace std;

/**
 * analog - Herramienta de análisis de logs de Apache
 * Uso: ./analog [options] nomfichier.log
 */
int main(int argc, char* argv[]) 
{
    string logFileName = "";
    string dotFileName = "";
    bool excludeResources = false;
    int selectedHour = -1;
    bool generateGraph = false;

    // 1. Procesamiento de argumentos [cite: 52, 53]
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [-g nomfichier.dot] [-e] [-t heure] nomfichier.log" << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-g" && i + 1 < argc) {
            generateGraph = true;
            dotFileName = argv[++i]; // 
        } else if (arg == "-e") {
            excludeResources = true; // [cite: 59]
        } else if (arg == "-t" && i + 1 < argc) {
            try {
                selectedHour = stoi(argv[++i]); // [cite: 61]
                if (selectedHour < 0 || selectedHour > 23) {
                    cerr << "Error: L'heure doit être comprise entre 0 et 23." << endl;
                    return 1;
                }
            } catch (...) {
                cerr << "Error: L'argument de -t doit être un entier." << endl;
                return 1;
            }
        } else {
            // El último argumento sin flag se considera el archivo de log [cite: 53]
            logFileName = arg;
        }
    }

    if (logFileName.empty()) {
        cerr << "Error: Aucun fichier de log spécifié." << endl;
        return 1;
    }

    // 2. Inicialización de componentes según tus archivos
    // Se asume que LogReader abre el archivo en su constructor (común en este TP)
    LogReader reader(logFileName); 
    LogStats stats(reader); //

    GraphMaker* grapher = nullptr;
    if (generateGraph) {
        grapher = new GraphMaker(dotFileName); //
    }

    // 3. Ejecución del análisis
    // Esta función ya gestiona internamente:
    // - El filtrado por hora y exclusión de estáticos.
    // - La llamada al generador de grafos si grapher != nullptr.
    // - El mostrado del Top 10 por consola.
    stats.AnalyseLogs(grapher, excludeResources, selectedHour);

    // 4. Limpieza
    if (grapher != nullptr) {
        delete grapher;
    }

    return 0;
}