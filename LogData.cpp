using namespace std;
#include "LogData.h"


LogData::LogData(string unFileName) {
	this->fileName = unFileName;
}

LogData::~LogData() {
}

void LogData::Get_info(const string & unLog ,string & heure , string & cible, 
						string & formatCib, string & ref, string & formatRef) {	
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
		formatRef = "\n";
	}
	cout << ref << endl;
	cout << formatRef << endl;
} 

/*void LogData::Insert_Cib(string cible) {
	try {
		int hits = dataRef.at(cible);
		dataRef.at(cible) = hits+1;
	}
	catch (const std::out_of_range& oor) {
		dataRef.insert(pair<string , int>(cible , 1));
	}
} */

void LogData::fetch_dataCib() {
	for (auto i:dataCibRef) 
		dataCib.insert(pair<int , string>(i.second.second , i.first));
}

void LogData::Insert_CibRef(string cible , string ref) {
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
}

void LogData::export_dot(string fileDot) {
	ofstream fic;
	fic.open(fileDot);
	fic << "digraph {" << endl;
	
	fic<< "}";
	fic.close();
}

void LogData::Affiche_data(vector<string> & options , string fileDot) {
	if (options.empty()) {
		int i;
		DataCib::reverse_iterator rit;
		fetch_dataCib();
		for (rit = dataCib.rbegin() , i=0; rit != dataCib.rend() && i < 10; ++rit , ++i)
			cout << rit->second << " (" << rit->first << " hits)" << endl;
	}
	else {
		cout << "Dot-file " << fileDot << " generated" << endl;
		for(auto i:dataCibRef) 
			cout << i.first << " (" << i.second.second << " hits)" << endl;
		export_dot(fileDot);
	}
}


