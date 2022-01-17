using namespace std;
#include "LogData.h"


int main(int argv , char* argc[]) {
	LogData logs(argc[argv-1]);
	ifstream fic;
	fic.open(argc[argv-1]);
	string heure;
	string unLog, cible, formatCib, ref, unString, fileDot;
	vector<string> options;
	for (int i = 1 ; i <= argv-2 ; ++i) {
		unString = string(argc[i]);
		options.push_back(unString); 
	}
	while (!fic.eof()) {
		getline(fic , unLog);
		logs.Get_info(unLog, heure, cible, formatCib, ref);
		logs.Insert_CibRef(cible , ref);	
	}
	
	if (options.empty()) {
		logs.Affiche_data(options);
	}
	else {
		for(int i = 0 ; i < options.size() ; ++i)
			if (options[i].compare("-g") == 0) fileDot = options[i+1];
		logs.Affiche_data(options , fileDot);
	}
	
	fic.close();
	return 0;
}
