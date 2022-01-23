/*************************************************************************
                          LogData
                             -------------------
    début                : 12 janvier 2022
    copyright            : (C) 2022 par NGO Ngoc Minh
    									PHAM Quoc Viet
*************************************************************************/

//---------- Réalisation de la classe <LogData> (fichier LogData.cpp) -------
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
using namespace std;
#include "LogData.h"

//----------------------------------------------------------------- PUBLIC	

//------------------------------------------------------------------------
void Get_info(const string & unLog ,string & heure , string & cible, 
						string & formatCib, string & ref, string & formatRef) {	
// Algorithme :
//
//
// 						
	size_t found, found1, found2, sz;
	string stringBase("http://intranet-if.insa-lyon.fr");
	found = unLog.find(':');
	found1 = unLog.find(':', found+1);
	heure.assign(unLog, found+1, found1-found-1);
	
	/*-----------*/
	found = unLog.find('\"', found1+1);
	found = unLog.find(' ', found+1);
	found1 = unLog.find(' ', found+1);
	cible.assign(unLog, found+1, found1-found-1);
	/*---------*/
	found2 = cible.find('.');
	formatCib.assign(cible, found2+1);
	/*--------*/
	found = unLog.find('\"', found1+1);
	found = unLog.find('\"', found+1);
	found1 = unLog.find('\"', found+1);
	ref.assign(unLog, found+1, found1-found-1);
	found = ref.find(stringBase);
	if (found != string::npos) {
		ref.erase(0 , stringBase.length());
		found1 = ref.find('.');
		formatRef.assign(ref, found1 + 1);
	}
	else {
		formatRef = "";
	}
} //----- Fin de Fonction ordinaire

void Fetch_dataCib(LogData & logData) {
// Algorithme :
//
//
// 	
	for (auto i:logData.dataCibRef) 
		logData.dataCib.insert(pair<int , string>(i.second.second , i.first));
} //----- Fin de Fonction ordinaire



void Export_dot(LogData & logData) {
// Algorithme :
//
//
// 	
	string unString1, unString2;
	ofstream fic;	
	
	DataCibRef::iterator it;
	DataRef::iterator it1;
	
	typedef multimap<int, pair<string, string>> MapLiens;
	MapLiens mapL; 
	typedef map <string, int> MapNodes;
	MapNodes mapN;
	bool inserted;
	int cibPos;
	int refPos;
	
	fic.open(logData.fileDot);
	
	fic << "digraph {" << endl;
	for (it = logData.dataCibRef.begin() ; it != logData.dataCibRef.end() ; ++it) {
		inserted = (mapN.insert(pair<string, int>(it->first, mapN.size()))).second;
		cibPos = mapN.at(it->first);
		if (inserted) {
			fic << "node" << cibPos << " [label = \"" << it->first << "\"];" << endl;
		}
		for (it1 = it->second.first.begin(); it1 !=  it->second.first.end() ; ++it1)
		{
			inserted = (mapN.insert(pair<string, int>(it1->first, mapN.size()))).second;
			refPos = mapN.at(it1->first);
			if (inserted) {
				fic << "node" << refPos << " [label = \"" << it1->first << "\"];" << endl;
			}
			
			unString1 = "node";		unString1.append(to_string(cibPos));
			unString2 = "node";		unString2.append(to_string(refPos));
			mapL.insert(pair<int, pair<string, string>>(it1->second, pair<string, string>(unString2, unString1)));
		}
	}
	
	for(auto elem:mapL) {
		fic << elem.second.first << " -> " << elem.second.second << "[label = " << elem.first << "];" << endl;
	}
	fic<< "}";
	fic.close();
} //----- Fin de Fonction ordinaire

void Insert_CibRef(LogData & logData , string cible , string ref) {
// Algorithme :
//
//
//
	try {
		// cas : key cible existe deja dans dataCibRef
		pair<DataRef,int> unPair;
		unPair = logData.dataCibRef.at(cible);
		int hits = logData.dataCibRef.at(cible).second;
		logData.dataCibRef.at(cible).second = hits+1;
		try {
			//cas : key ref existe deja dans dataRef
			int nbCibRef = logData.dataCibRef.at(cible).first.at(ref);
			logData.dataCibRef.at(cible).first.at(ref) = nbCibRef+1;
		}
		catch (const std::out_of_range& oor1) {
			// cas : key ref n'existe pas encore dans dataRef
			logData.dataCibRef.at(cible).first.insert(pair<string,int>(ref , 1));
		}
	}
	catch (const std::out_of_range& oor) {
		// cas : key cible n'existe pas encore dans dataCibRef
		pair<DataRef,int> unPair;
		unPair.first.insert(pair<string,int>(ref , 1));
		unPair.second = 1; // hits = 1 
		logData.dataCibRef.insert(pair<string,pair<DataRef,int>>(cible , unPair));
	}
} //----- Fin de Fonction ordinaire

//----------------------------------------------------- Méthodes publiques
void LogData::Line_Manager(const string & unLog, bool optionG, bool optionE, bool optionT, string uneHeure) {
// Algorithme :
//
//
// 
	bool formatCibNonPris, formatRefNonPris;
	string heure, cible, formatCib, ref, formatRef;
	Get_info(unLog, heure, cible, formatCib, ref, formatRef);
	
	if (optionT && heure.compare(uneHeure) != 0) {
		return;
	}
	
	if (optionE) {
		formatCibNonPris = (formatCib == "jpg") || (formatCib == "css") || (formatCib == "js");
		formatRefNonPris = (formatRef == "jpg") || (formatRef == "css") || (formatRef == "js");
		if (formatCibNonPris || formatRefNonPris) {
			return;
		}
	}
	Insert_CibRef(*this, cible , ref);	
} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs

ostream & operator<<(ostream & out, LogData & logData) {
	int i;
	DataCib::reverse_iterator rit;
	Fetch_dataCib(logData);
	if (logData.fileDot.compare("") != 0) {
		out << "Dot-file " << logData.fileDot << " generated" << endl;
		Export_dot(logData);
	}
	for (rit = logData.dataCib.rbegin() , i=0; rit != logData.dataCib.rend() && i < 10; ++rit , ++i)
		out << rit->second << " (" << rit->first << " hits)" << endl;
	return out;	
} //----- Fin de operator <<

//-------------------------------------------- Constructeurs - destructeur
LogData::LogData(string unFileName, string unFileDot) {
	this->fileName = unFileName;
	this->fileDot = unFileDot;
#ifdef MAP
    cout << "Appel au constructeur de <LogData>" << endl;
#endif
} //----- Fin de LogData

LogData::~LogData() { 
#ifdef MAP
    cout << "Appel au destructeur de <LogData>" << endl;
#endif
} //----- Fin de ~LogData
