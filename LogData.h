#if ! defined (LOG_DATA_H)
#define LOG_DATA_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
class LogData {

public:
	LogData(string);
	LogData(const LogData&);
	~LogData();
	
	void Insert_Link(string , string);
	void Insert_Linkref(string);
private:
	typedef map<string , int> DataRef; //string : URL ref
	DataRef dataRef;
	typedef map<string , pair<DataRef , int>> LogApache; //string : URL cible
	LogApache logApache;
	string fileName;
};

#endif
