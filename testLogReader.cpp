#include <iostream>
#include "LogReader.h"
#include "LogEntry.h"

using namespace std;

void afficherLog(const LogEntry& e) {
    cout << "------------------------------------------" << endl;
    cout << "IP Client    : " << e.client_ip << endl;
    cout << "Date & Heure : " << e.date << " à " << e.time << " (" << e.hour << ")" << endl;
    cout << "Action       : " << e.action << endl;
    cout << "URL          : " << e.url << endl;
    cout << "Document Type: " << e.document_type << endl;
    cout << "Protocole    : " << e.protocol << endl;
    cout << "Code Retour  : " << e.r_code << endl;
    cout << "Taille       : " << e.size << " octets" << endl;
    cout << "Referer      : " << e.referer << endl;
    cout << "Navigateur   : " << e.client_id << endl;
}

int main() {
    LogReader reader("./anonyme.log");
    
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
