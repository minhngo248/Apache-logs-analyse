main: main.cpp
	g++ -c main.cpp
LogData: LogData.cpp
	g++ -c LogData.cpp
analog: main.o LogData.o
	g++ -o analog *.o
Run: analog
	./analog A.log