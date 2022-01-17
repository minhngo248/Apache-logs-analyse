#if ! defined (LOG_DATA_H)
#define LOG_DATA_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>      // std::out_of_range
#include <map>
#include <vector>
class LogData 
{
public:
	LogData(string unFileName);
	LogData(const LogData&);
	~LogData();
	
	void Insert_CibRef(string cible , string ref);
	void Affiche_data(vector<string> & options , string fileDot = "");
	void Get_info(const string & unLog, string& heure, string& cible, string& formatCib, string& ref);
	
private:
	void fetch_dataCib();
	void export_dot(string fileDot);
	typedef multimap<int , string> DataCib; // pour le cas de sans option
	DataCib dataCib; 
	typedef map<string , int> DataRef; //string : URL cible, int : hits
	typedef map<string , pair<DataRef , int>> DataCibRef; 
	// string : URL cible 
	// string de DataRef : URL ref , int de DataRef : nombre acces de ref->cib
	// int de pair : hits
	// 
	DataCibRef dataCibRef;
	string fileName;
};

#endif
