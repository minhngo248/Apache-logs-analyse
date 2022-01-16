using namespace std;
#include "LogData.h"


LogData::LogData(string unFileName) {
	this->fileName = unFileName;
}

LogData::~LogData() {
}

void LogData::Insert_Cib(string cible) {
	try {
		int hits = dataRef.at(cible);
		dataRef.at(cible) = hits+1;
	}
	catch (const std::out_of_range& oor) {
		dataRef.insert(pair<string , int>(cible , 1));
	}
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

void LogData::Export_dot(string fileDot) {
	ofstream fic;
	fic.open(fileDot);
	fic << "digraph {" << endl;
	/*-------- pas fini --------*/
	fic.close();
}

void LogData::Affiche_data(vector<string> & options , string fileDot) {
	if (options.empty()) {
		for(auto i:dataRef) 
			cout << i.first << " (" << i.second << " hits)" << endl;
	}
	else {
		cout << "Dot-file " << fileDot << " generated" << endl;
		for(auto i:dataCibRef) 
			cout << i.first << " (" << i.second.second << " hits)" << endl;
		Export_dot(fileDot);
	}
}

void LogData::Test_affiche_data() {
	cout << "Cible" << '\t' << "Ref" << '\t' << "R->C" << '\t' << "hits" << endl;
	for(auto i:dataCibRef) {
		for (DataRef::iterator j = i.second.first.begin() ; j != i.second.first.end() ; j++)
			cout << i.first << '\t' << j->first <<  '\t' 
			<< j->second << '\t' << i.second.second << endl;
	}
}
