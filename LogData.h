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
	// type M�thode ( liste des param�tres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
//------------------------------------------------- Surcharge d'op�rateurs
	friend ostream & operator<<(ostream & out, LogData & unLog);
	
//-------------------------------------------- Constructeurs - destructeur
	LogData(string unFileName, string unFileDot);
	LogData(const LogData & unLog);
	~LogData();
	
//------------------------------------------------------------------ PRIVE	
private:
//------------------------------------------------------- M�thodes priv�es	
	void get_info(const string & unLog, string& heure, 
				string& cible, string& formatCib, string& ref, string& formatRef);
	void fetch_dataCib();
	void export_dot();
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
