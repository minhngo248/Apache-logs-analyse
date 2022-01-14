using namespace std;
#include "LogData.h"


LogData::LogData(string unFileName) {
	this->fileName = unFileName;
}

LogData::~LogData() {
}

void LogData::Insert_Cib(string cible) {
	int m;
	try {
		m = dataRef.at(cible);
		dataRef.at(cible) = m+1;
	}
	catch (const std::out_of_range& oor) {
		dataRef.insert(pair<string , int>(cible , 1));
	}
}

void LogData::Insert_CibRef(string cible , string ref) {

}

void LogData::Affiche_data() {
	for(auto i:dataRef) {
		if (i.second <= 1)
			cout << i.first << " (" << i.second << " hit)" << endl;
		else 
			cout << i.first << " (" << i.second << " hits)" << endl;
	}
}
