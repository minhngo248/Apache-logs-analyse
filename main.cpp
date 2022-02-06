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
	ifstream fic;
	if (argc < 2) {
		cerr << "Erreur : Vous avez oublie le fichier log" << endl;
		return 1;
	}else if (string(argv[argc-1]).find(".log") == string::npos) {
		cerr << "Erreur : Vous avez oublie le fichier log" << endl;
		return 1;
	}else{
		fic.open(argv[argc-1]);
	}
	
	if (!fic.is_open()) {
		cerr << "Fichier n'existe pas" << endl;
		return 1;
	}
	string heure = "";
	string unLog, unString, fileDot = "";
	bool optionG = false, optionT = false, optionE = false;
	
	for (int i = 1 ; i <= argc-2 ; ++i) {
		unString = string(argv[i]);
		if (unString == "-g") {
			optionG = true;
			fileDot = string(argv[i+1]);
			if (fileDot.find(".dot") == string::npos && fileDot.find(".txt") == string::npos) {
				cerr << "Erreur : Vous avez oublie le fichier dot" << endl;
				return 1;
			}
		}
		else if (unString == "-e") {
			optionE = true;
		}
		else if (unString == "-t") {
			optionT = true;
			heure = string(argv[i+1]);
			if (stoi(heure) <0 || stoi(heure) >23) {
				cerr << "Erreur : Heure invalide" << endl;
				return 1;
			}
		}
	}
	LogData logs(argv[argc-1] , fileDot);
	
	while (!fic.eof()) {
		getline(fic , unLog);
		logs.Line_Manager(unLog, optionG, optionE, optionT, heure);		
	}	
	
	cout << logs;
	
	fic.close();
	return 0;
}
