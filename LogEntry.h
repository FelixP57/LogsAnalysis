#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <string>

using namespace std;

struct LogEntry{
    string client_ip;
    string date;
    string time; //Contient time + fuseau horaire
    int hour;
    string action; // GET/POST/OPTIONS/...
    string url; //URL demandé
    string document_type;
    string protocol;
    int r_code; //Code retour
    int size; //Taille en octets de la réponse
    string referer; //URL de la page source
    string client_id; //Identifiant du navigateur client
};

#endif
