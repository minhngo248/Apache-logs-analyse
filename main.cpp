/*************************************************************************
                            main 
                             -------------------
    debut                : 12 janvier 2022
    copyright            : (C) 2022 par NGO Ngoc Minh 
										PHAM Quoc Viet
*************************************************************************/
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
using namespace std;
#include "LogData.h"


int main(int argc , char* argv[]) {
	LogData logs(argv[argc-1]);
	ifstream fic;
	fic.open(argv[argc-1]);
	
	
	string heure = "";
	string unLog, unString, fileDot = "";
	bool optionG = false, optionT = false, optionE = false;
	
	for (int i = 1 ; i <= argc-2 ; ++i) {
		unString = string(argv[i]);
		if (unString == "-g") {
			optionG = true;
			fileDot = string(argv[i+1]);
		}
		if (unString == "-e") {
			optionE = true;
		}
		if (unString == "-t") {
			optionT = true;
			heure = string(argv[i+1]);
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
