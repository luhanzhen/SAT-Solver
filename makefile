
CXX = g++ --std=c++17

CXXFLAGS= -Wall

EXE = exe

obj = Formul.o Genetic_Algorithm.o DPLL.o WalkSat.o SAT.o

all: $(EXE)

$(EXE):$(obj)
	$(CXX) $(CXXFLAGS)  -o $(EXE)  $(obj)
Formul.o: Formul.cpp Formul.h
	$(CXX)  $(CXXFLAGS) -c Formul.cpp 
Genetic_Algorithm.o:Genetic_Algorithm.cpp Genetic_Algorithm.h
	$(CXX)  $(CXXFLAGS) -c Genetic_Algorithm.cpp
DPLL.o:DPLL.cpp DPLL.h
	$(CXX)  $(CXXFLAGS) -c DPLL.cpp
WalkSat.o:WalkSat.cpp WalkSat.h
	$(CXX)  $(CXXFLAGS) -c WalkSat.cpp
SAT.o:SAT.cpp Tools.h
	$(CXX)  $(CXXFLAGS) -c SAT.cpp

.PHONY : clean all
clean:
	rm -f $(EXE)  $(obj)
