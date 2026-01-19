main: analog.cpp LogReader.o LogStats.o GraphMaker.o
	g++ -o test analog.cpp LogReader.o LogStats.o GraphMaker.o

LogReader.o: LogReader.h LogEntry.h
	g++ -c LogReader.cpp

LogStats.o: LogStats.h LogReader.h GraphMaker.h
	g++ -c LogStats.cpp

GraphMaker.o: GraphMaker.h
	g++ -c GraphMaker.cpp

