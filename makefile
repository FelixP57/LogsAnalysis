main: analog.cpp LogReader.o LogStats.o GraphMaker.o
	g++ -o analog analog.cpp LogReader.o LogStats.o GraphMaker.o -std=c++11

LogReader.o: LogReader.h LogEntry.h
	g++ -c LogReader.cpp -std=c++11

LogStats.o: LogStats.h LogReader.h GraphMaker.h
	g++ -c LogStats.cpp -std=c++11

GraphMaker.o: GraphMaker.h
	g++ -c GraphMaker.cpp -std=c++11

