# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O3
EXEC = analog
SRC = analog.cpp LogReader.cpp LogStats.cpp GraphMaker.cpp
OBJ = $(SRC:.cpp=.o)

# Règle principale
all: $(EXEC)

# Linkage
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

# Compilation des objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f *.o $(EXEC)

# Dépendances spécifiques
LogReader.o: LogReader.h LogEntry.h
LogStats.o: LogStats.h LogReader.h GraphMaker.h LogEntry.h
GraphMaker.o: GraphMaker.h