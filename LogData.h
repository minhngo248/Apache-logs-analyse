/*************************************************************************
                          LogData - un objet pour sauvegarder 
							tous les lignes Log
                             -------------------
    d�but                : 12 janvier 2022
    copyright            : (C) 2022 par NGO Ngoc Minh
    									PHAM Quoc Viet
*************************************************************************/

//---------- Interface de la classe <LogData> (fichier LogData.h) ------
#if ! defined (LOG_DATA_H)
#define LOG_DATA_H
//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>      // std::out_of_range
#include <map>

//------------------------------------------------------------------ Types
typedef multimap<int, string> DataCib;
typedef map<string , int> DataRef; 
typedef map<string , pair<DataRef , int>> DataCibRef; 

//------------------------------------------------------------------------ 
// R�le de la classe <LogData>
//
//
//------------------------------------------------------------------------ 
class LogData {
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- M�thodes publiques	
	void Line_Manager(const string & unLog, bool optionG, bool optionE, bool optionT, string uneHeure);
    // Mode d'emploi : A partir de chaque ligne dans le fichier log, cette m�thode extrait
    // les informations n�cessaires et les ajoute dans notre structure de donn�es si possible
    // 
    //
    
//------------------------------------------------- Surcharge d'op�rateurs
	friend ostream & operator<<(ostream & out, LogData & unLog) ;
	// Mode d'emploi : affiche les URL cibles et le nombre de clics selon
    // option de ligne de commandes
    // 
    //
	
//-------------------------------------------- Constructeurs - destructeur
	LogData(string unFileName, string unFileDot);
	LogData(const LogData & unLog);
	~LogData();
	
//------------------------------------------------------------------ PRIVE	
private:
//------------------------------------------------------- M�thodes priv�es	
	void get_info(const string & unLog, string& heure, 
				string& cible, string& formatCib, string& ref, string& formatRef);
	// Mode d'emploi : prendre les attributs dans une ligne de log
    //
    // 
    //
	void fetch_dataCib();
	// Mode d'emploi : entr�e les valeurs dans le multimap DataCib
    //
    // 
    //
	void export_dot();
	// Mode d'emploi : exporter le fichier .dot
    //
    // 
    //
	void insert_CibRef(string cible, string ref);
//------------------------------------------------------ Attributs priv�es
	DataCib dataCib; //string : URL cible, int : hits
	DataCibRef dataCibRef;
	// string : URL cible 
	// string de DataRef : URL ref , int de DataRef : nombre acces de ref->cib
	// int de pair : hits
	//
	string fileName;
	string fileDot;
};

#endif // ! defined (LOG_DATA_H)
