/*************************************************************************
                          LogData - un objet pour sauvegarder 
							tous les lignes Log
                             -------------------
    début                : 12 janvier 2022
    copyright            : (C) 2022 par NGO Ngoc Minh
    									PHAM Quoc Viet
*************************************************************************/

//---------- Interface de la classe <LogData> (fichier LogData.h) ------
#if ! defined (LOG_DATA_H)
#define LOG_DATA_H
//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>      // std::out_of_range
#include <map>
//------------------------------------------------------------------------ 
// Rôle de la classe <LogData>
//
//
//------------------------------------------------------------------------ 
class LogData {
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques	
	void Line_Manager (string & unLog, bool optionG, bool optionE, bool optionT, string fileDot, string uneHeure);
	// type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
	void Insert_CibRef(string cible , string ref);
	void Affiche_data(string fileDot = "");
	//-------------------------------------------- Constructeurs - destructeur
	LogData(string unFileName);
	LogData(const LogData&);
	~LogData();
//------------------------------------------------------------------ PRIVE	
private:
//------------------------------------------------------- Méthodes privées	
	void get_info(const string & unLog, string& heure, 
				string& cible, string& formatCib, string& ref, string& formatRef);
	void fetch_dataCib();
	void export_dot(string fileDot);
//----------------------------------------------------- Attributs prives
	typedef multimap<int , string> DataCib; // pour le cas de sans option
	DataCib dataCib; 
	typedef map<string , int> DataRef; //string : URL cible, int : hits
	typedef map<string , pair<DataRef , int>> DataCibRef; 
	// string : URL cible 
	// string de DataRef : URL ref , int de DataRef : nombre acces de ref->cib
	// int de pair : hits
	// 
	DataCibRef dataCibRef;
	string fileName;
};

#endif // ! defined (LOG_DATA_H)
