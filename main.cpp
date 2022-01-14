#include <iostream>
#include <fstream>
using namespace std;
#include "LogData.h"

int main(int argv , char* argc[]) {
	LogData logs(argc[argv-1]);
	ifstream fic;
	fic.open(argc[argv-1]);
	string unLog, cible;
	size_t found, found1;
	
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
		/*--------*/
	/*	found = unLog.find('\"' , found2);
		found1 = unLog.find('\"', found+1);
		ref.assign(unLog, found+1, found1-found-1);
		cout << cible << '\t' << ref << endl;
		i++; */
	}
	logs.Affiche_data();
	fic.close();
	return 0;
}
