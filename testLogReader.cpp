#include "LogReader.h"
#include "LogEntry.h"
#include <iostream>
#include <iomanip> // Pour un affichage plus propre

using namespace std;

void afficherLog(const LogEntry& e) {
    cout << "------------------------------------------" << endl;
    cout << "IP Client    : " << e.client_ip << endl;
    cout << "Date & Heure : " << e.date << " à " << e.time << endl;
    cout << "Action       : " << e.action << endl;
    cout << "URL          : " << e.url << endl;
    cout << "Protocole    : " << e.protocol << endl;
    cout << "Code Retour  : " << e.r_code << endl;
    cout << "Taille       : " << e.size << " octets" << endl;
    cout << "Referer      : " << e.referer << endl;
    cout << "Navigateur   : " << e.client_id << endl;
}

int main() {
    LogReader reader("/Users/jbrisard/Documents/IF/ProgC++/TP4/LogsAnalysis/anonyme.log");
    
    // On teste sur les 3 premières lignes
    for(int i = 0; i < 3; ++i) {
        LogEntry entry = reader.readLine();
        if (!entry.client_ip.empty()) {
            cout << "\nLECTURE DE LA LIGNE " << i+1 << " :" << endl;
            afficherLog(entry);
        }
    }

    return 0;
}