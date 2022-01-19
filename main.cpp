using namespace std;
#include "LogData.h"


int main(int argv , char* argc[]) {
	LogData logs(argc[argv-1]);
	ifstream fic;
	fic.open(argc[argv-1]);
	
	
	string heure = "";
	string unLog, unString, fileDot = "";
	bool optionG = false, optionT = false, optionE = false;
	
	for (int i = 1 ; i <= argv-2 ; ++i) {
		unString = string(argc[i]);
		if (unString == "-g") {
			optionG = true;
			fileDot = string(argc[i+1]);
		}
		if (unString == "-e") {
			optionE = true;
		}
		if (unString == "-t") {
			optionT = true;
			heure = string(argc[i+1]);
		}
	}
	
	while (!fic.eof()) {
		getline(fic , unLog);
		logs.Line_Manager(unLog, optionG, optionE, optionT, fileDot, heure);		
	}	
	
	logs.Affiche_data(fileDot);
	
	fic.close();
	return 0;
}
