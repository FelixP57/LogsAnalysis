#include <iostream>
#include <string>
#include <vector>

// Estas cabeceras representarían las clases que debes desarrollar 
// según la sección "Conception" del TP.
#include "LogStats.h"

using namespace std;

/**
 * Función principal para la herramienta 'analog'[cite: 50, 53].
 * Estructura de comando: ./analog [options] nomfichier.log
 */
int main(int argc, char* argv[]) 
{
    // Variables para almacenar los parámetros de las opciones [cite: 52]
    string logFileName = "";
    string dotFileName = "";
    bool excludeResources = false; // Opción -e [cite: 59, 60]
    int selectedHour = -1;         // Opción -t [cite: 61, 62]
    bool generateGraph = false;    // Opción -g [cite: 56, 57]

    // 1. Tratamiento de los argumentos de la línea de comandos [cite: 52]
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " [-g nomfichier.dot] [-e] [-t heure] nomfichier.log" << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-g" && i + 1 < argc) {
            generateGraph = true;
            dotFileName = argv[++i]; // El siguiente argumento es el archivo .dot [cite: 56]
        } else if (arg == "-e") {
            excludeResources = true; // Excluir imágenes, css, js [cite: 60]
        } else if (arg == "-t" && i + 1 < argc) {
            try {
                selectedHour = stoi(argv[++i]); // Intervalo [heure, heure+1[ [cite: 62]
            } catch (...) {
                cerr << "Error: La hora debe ser un número entero." << endl;
                return 1;
            }
        } else {
            // Se asume que el último argumento sin flag es el archivo de log [cite: 53]
            logFileName = arg;
        }
    }

    // 2. Validación de archivo de entrada
    if (logFileName.empty()) {
        cerr << "Error: No se especificó un archivo de log." << endl;
        return 1;
    }

    // 3. Ejecución de la lógica mediante la clase LogReader [cite: 72, 82]
    LogStats analyzer;

    // Configurar filtros según las opciones capturadas
    if (excludeResources) {
        analyzer.EnableResourceFiltering(); 
    }
    if (selectedHour != -1) {
        analyzer.SetTimeFilter(selectedHour);
    }

    // Procesar el archivo [cite: 81]
    if (!analyzer.LoadLogs(logFileName)) {
        cerr << "Error al abrir o leer el archivo: " << logFileName << endl;
        return 1;
    }
    
    // Si se activó -g, generar el archivo GraphViz [cite: 57]
    if (generateGraph) {
        if (analyzer.ExportToDot(dotFileName)) {
            cout << "Dot-file " << dotFileName << " generated" << endl;
        }
    }

    // Por defecto, mostrar el Top 10 en consola [cite: 54]
    analyzer.DisplayTop10();

    return 0;
}