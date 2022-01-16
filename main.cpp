using namespace std;
#include "LogData.h"


int main(int argv , char* argc[]) {
	LogData logs(argc[argv-1]);
	ifstream fic;
	fic.open(argc[argv-1]);
	string unLog, cible, ref;
	string unString;
	size_t found, found1, found2;
	vector<string> options;
	for (int i = 1 ; i <= argv-2 ; ++i) {
		unString = string(argc[i]);
		options.push_back(unString); 
	}
	
	if (argv == 2) {
		while (!fic.eof()) {
			// cas : sans option
			getline(fic , unLog);
			found = unLog.find('\"');
			found1 = unLog.find('\"' , found+1);
			cible.assign(unLog , found+1 , found1-found-1);
			/*-------*/
			found = cible.find(' ');
			found1 = cible.find(' ', found+1);
			cible.assign(cible, found+1, found1-found-1);
			logs.Insert_Cib(cible);	
		}
		logs.Affiche_data(options);
	}
	else if (argv > 2) {
		while (!fic.eof()) {
			getline(fic , unLog);
			found = unLog.find('\"');
			found1 = unLog.find('\"' , found+1);
			found2 = found1+1;
			cible.assign(unLog , found+1 , found1-found-1);
			/*-------*/
			found = cible.find(' ');
			found1 = cible.find(' ', found+1);
			cible.assign(cible, found+1, found1-found-1);
			/*--------*/
			found = unLog.find('\"' , found2);
			found1 = unLog.find('\"', found+1);
			ref.assign(unLog, found+1, found1-found-1);
			logs.Insert_CibRef(cible , ref);	
		}
		string fileDot;
		fileDot.assign(options[1]);
		logs.Affiche_data(options , fileDot);
	}
	fic.close();
	return 0;
}
