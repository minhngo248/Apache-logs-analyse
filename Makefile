main: main.cpp
	g++ -c main.cpp -std=c++11
LogData: LogData.cpp
	g++ -c LogData.cpp -D MAP -std=c++11
analog: main.o LogData.o
	g++ -o analog *.o -D MAP -std=c++11
Run: analog
	./analog A.log