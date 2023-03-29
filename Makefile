CXX 		= g++
CXXFLAGS 	= -g -std=c++2a
PROJ 		= bratleys
OBJ	 		= main.o job.o node.o # tree.o

all: $(PROJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(PROJ): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	rm $(PROJ) $(OBJ)
