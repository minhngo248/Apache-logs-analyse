#if ! defined (LOG_DATA_H)
#define LOG_DATA_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>      // std::out_of_range
#include <map>
#include <vector>
#include <iterator>
class LogData 
{
public:
	LogData(string unFileName);
	LogData(const LogData&);
	~LogData();
	
	void Insert_Cib(string cible);
	void Insert_CibRef(string cible , string ref);
	void Affiche_data(vector<string> & options , string fileDot = "");
	void Test_affiche_data();
	void Export_dot(string fileDot);
private:
	typedef map<string , int> DataRef; //string : URL cible, int : hits
	DataRef dataRef;
	typedef map<string , pair<DataRef , int>> DataCibRef; 
	// string : URL cible 
	// string de DataRef : URL ref , int de DataRef : nombre acces de ref->cib
	// int de pair : hits
	// 
	DataCibRef dataCibRef;
	string fileName;
};

#endif
