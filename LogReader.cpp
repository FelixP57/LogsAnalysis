/*************************************************************************
	       LogReader  -  Reads and parses an Apache Log 
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
					      Jules BRISARD
					      Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Réalisation de la classe <LogReader> (fichier LogReader.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "LogReader.h"
#include "LogEntry.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

LogEntry LogReader::readLine()
// Algorithme :
// 1. Lecture de la ligne brute du fichier log
// 2. Parsing de l'adresse IP et des champs vides
// 3. Extraction de la date et l'heure entre crochets
// 4. Extraction de la requête HTTP (action, URL, protocole)
// 5. Récupération du code de retour et de la taille de la réponse
// 6. Extraction du referer et du user agent entre guillemets
// Retour : Un objet LogEntry complètement rempli
{
    string line;
    LogEntry log;
    // On récupère une ligne brute du fichier
    if (!getline(logstream, line))
	return log;
    
    // On transforme la ligne en flux pour la découper
    istringstream iss(line); 
    
    string dump; // Variable poubelle pour stocker les tirets "-"
    char car_ignore; // Pour consommer les crochets ou guillemets

    // 1. Lecture de l'IP et des champs inutiles (- -)
    iss >> log.client_ip >> dump >> dump;

    // 2. Lecture de la Date : [08/Sep/2012:11:16:02 +0200]
    iss.ignore(); // On saute l'espace avant le crochet
    iss.ignore(); // On saute le crochet ouvrants '['
    
    // On lit jusqu'au crochet fermant ']'
    string full_date_time;
    getline(iss, full_date_time, ']');
    
    // On peut redécouper full_date_time maintenant
    // Le format est "date:time". On cherche le ':'
    size_t pos_deux_points = full_date_time.find(':');
    if (pos_deux_points != string::npos) {
        log.date = full_date_time.substr(0, pos_deux_points);
        log.time = full_date_time.substr(pos_deux_points + 1);
    }

    // On récupère l'heure
    log.hour = stoi(log.time.substr(0, 2));

    iss.ignore(); // On saute l'espace après le ']'

    // 3. Lecture de la requête complète : "GET /url HTTP/1.1"
    iss.ignore(); // On saute le guillemet ouvrant '"'
    string full_request;
    getline(iss, full_request, '"');
    
    // La requête contient 3 infos séparées par des espaces. 
    // On refait un stream local juste pour ce bout de chaîne !
    stringstream ss_request(full_request);
    ss_request >> log.action >> log.url >> log.protocol;

    size_t pos_point = log.url.find('.');
    log.document_type = "";
    if (pos_point != string::npos) {
	log.document_type = log.url.substr(pos_point+1, log.url.length() - pos_point);
    } 

    iss.ignore(); // On saute l'espace après le guillemet fermant

    // 4. Code retour et Taille
    iss >> log.r_code;
    
    // Attention : la taille peut être un tiret "-" si 0 octet
    string size_str;
    iss >> size_str;
    if (size_str == "-") {
        log.size = 0;
    } else {
        log.size = stoi(size_str);
    }

    // 5. Referer : "http://..."
    iss.ignore(); // Espace
    iss.ignore(); // Guillemet "
    getline(iss, log.referer, '"');

    string base_url = "http://intranet-if.insa-lyon.fr";
    size_t pos_base_url = log.referer.find(base_url);
    if (pos_base_url != string::npos) {
	log.referer = log.referer.substr(pos_base_url + base_url.length(), log.referer.length()-pos_base_url-base_url.length());
    }

    size_t pos_symbol = log.referer.find('?');
    if (pos_base_url != string::npos) {
	log.referer = log.referer.substr(0, pos_symbol);
    }
    pos_symbol = log.referer.find(';');
    if (pos_base_url != string::npos) {
	log.referer = log.referer.substr(0, pos_symbol);
    }
    pos_symbol = log.referer.find('#');
    if (pos_base_url != string::npos) {
	log.referer = log.referer.substr(0, pos_symbol);
    }

    // 6. User Agent : "Mozilla/5.0 ..."
    iss.ignore(); // Espace
    iss.ignore(); // Guillemet "
    getline(iss, log.client_id, '"');

    return log;
} //----- Fin de readLine


//-------------------------------------------- Constructeurs - destructeur

LogReader::LogReader ( const LogReader & unLogReader )
// Mode d'emploi : Constructeur de copie
// Algorithme : Affiche un message d'avertissement (copie dangereuse et inutile)
{
    cout<<"ATTENTION: Appel du constructeur de copie de LogReader, mais copie dangereuse";

} //----- Fin du constructeur de copie


LogReader::LogReader(const string& file_path)
// Mode d'emploi : Constructeur normal
// Algorithme : 
// 1. Ouverture du fichier log à partir du chemin spécifié
// 2. Vérification de la validité de l'ouverture
// 3. Affichage d'un message de succès ou d'erreur
{
    logstream.open(file_path.c_str());

    // VERIFICATION INDISPENSABLE
    if (!logstream.is_open()) {
        cerr << "ERREUR FATALE : Le fichier n'a pas pu être ouvert !" << endl;
        cerr << "Chemin tenté : " << file_path << endl;
        cerr << "Vérifiez que le dossier 'LogsAnalysis' existe bien là où vous lancez l'exécutable." << endl;
    } else {
        cout << "SUCCES : Fichier ouvert correctement." << endl;
    }
} //----- Fin du constructeur normal


LogReader::~LogReader ( )
// Mode d'emploi : Destructeur
// Algorithme : Ferme le flux de fichier et affiche un message de trace si MAP est défini
{
#ifdef MAP
    cout << "Appel au destructeur de <LogReader>" << endl;
#endif
} //----- Fin de ~LogReader


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
