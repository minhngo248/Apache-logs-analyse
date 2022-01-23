/*************************************************************************
                          LogData
                             -------------------
    d�but                : 12 janvier 2022
    copyright            : (C) 2022 par NGO Ngoc Minh
    									PHAM Quoc Viet
*************************************************************************/

//---------- R�alisation de la classe <LogData> (fichier LogData.cpp) -------
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

//------------------------------------------------------ Include personnel
using namespace std;
#include "LogData.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
void LogData::Line_Manager (string & unLog, bool optionG, bool optionE, bool optionT, string fileDot, string uneHeure) {
// Algorithme :
//
//
// 
	bool formatCibNonPris, formatRefNonPris;
	string heure, cible, formatCib, ref, formatRef;
	get_info(unLog, heure, cible, formatCib, ref, formatRef);
	
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
	
	Insert_CibRef(cible , ref);	
} //----- Fin de M�thode

void LogData::Insert_CibRef(string cible , string ref) {
// Algorithme :
//
//
//
	try {
		// cas : key cible existe deja dans dataCibRef
		pair<DataRef,int> unPair;
		unPair = dataCibRef.at(cible);
		int hits = dataCibRef.at(cible).second;
		dataCibRef.at(cible).second = hits+1;
		try {
			//cas : key ref existe deja dans dataRef
			int nbCibRef = dataCibRef.at(cible).first.at(ref);
			dataCibRef.at(cible).first.at(ref) = nbCibRef+1;
		}
		catch (const std::out_of_range& oor1) {
			// cas : key ref n'existe pas encore dans dataRef
			dataCibRef.at(cible).first.insert(pair<string,int>(ref , 1));
		}
	}
	catch (const std::out_of_range& oor) {
		// cas : key cible n'existe pas encore dans dataCibRef
		pair<DataRef,int> unPair;
		unPair.first.insert(pair<string,int>(ref , 1));
		unPair.second = 1; // hits = 1 
		dataCibRef.insert(pair<string,pair<DataRef,int>>(cible , unPair));
	}
} //----- Fin de M�thode

void LogData::Affiche_data(string fileDot) {
	int i;
	DataCib::reverse_iterator rit;
	fetch_dataCib();
	if (fileDot.compare("") !=0) {
		cout << "Dot-file " << fileDot << " generated" << endl;
		export_dot(fileDot);
	}
	for (rit = dataCib.rbegin() , i=0; rit != dataCib.rend() && i < 10; ++rit , ++i)
		cout << rit->second << " (" << rit->first << " hits)" << endl;	
}

//------------------------------------------------------------------ PRIVE	

//------------------------------------------------------- M�thodes priv�es
void LogData::get_info(const string & unLog ,string & heure , string & cible, 
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
} //----- Fin de M�thode

void LogData::fetch_dataCib() {
// Algorithme :
//
//
// 	
	for (auto i:dataCibRef) 
		dataCib.insert(pair<int , string>(i.second.second , i.first));
} //----- Fin de M�thode



void LogData::export_dot(string fileDot) {
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
	
	fic.open(fileDot);
	
	fic << "digraph {" << endl;
	for (it = dataCibRef.begin() ; it != dataCibRef.end() ; ++it) {
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
} //----- Fin de M�thode

//-------------------------------------------- Constructeurs - destructeur
LogData::LogData(string unFileName) {
	this->fileName = unFileName;
#ifdef MAP
    cout << "Appel au constructeur de <LogData>" << endl;
#endif
} //----- Fin de LogData

LogData::~LogData() { 
#ifdef MAP
    cout << "Appel au destructeur de <LogData>" << endl;
#endif
} //----- Fin de ~LogData
