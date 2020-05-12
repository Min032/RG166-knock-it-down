PROGRAM = Knock
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra
LDLIBS = -lglut -lGLU -lGL -lm

$(PROGRAM) : shapes.o callbackFunctions.o main.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS) && ./Knock

callbackFunctions.o: callbackFunctions.cpp callbackFunctions.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

shapes.o: shapes.cpp shapes.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

.PHONY : clean

clean: 
	-rm *.o
