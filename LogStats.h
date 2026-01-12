/*************************************************************************
	       LogStats  -  Generates stats for Apache Logs 
		 -------------------
    début                : 2026
    copyright            : (C) 12-01-2026 par Félix PIETRUCZANIS,
                                              Raphaël GUTEVILLE
					      Jules BRISARD
					      Gerald CHAMBI RAMOS
*************************************************************************/

//---------- Interface de la classe <LogStats> (fichier LogStats.h) ----------------
#if ! defined ( LOGSTATS_H )
#define LOGSTATS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogStats>
//
//
//------------------------------------------------------------------------

class LogStats : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    LogStats & operator = ( const LogStats & unLogStats );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    LogStats ( const LogStats & unLogStats );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    LogStats ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~LogStats ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <LogStats>

#endif // LOGSTATS_H

