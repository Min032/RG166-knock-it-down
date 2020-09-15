PROGRAM = Knock
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS = -lglut -lGLU -lGL -lm

$(PROGRAM) : shapes.o callbackFunctions.o helperFunctions.o main.o image.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) && ./Knock

helperFunctions.o: helperFunctions.cpp helperFunctions.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

callbackFunctions.o: callbackFunctions.cpp callbackFunctions.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

shapes.o: shapes.cpp shapes.hpp image.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

image.o: image.cpp image.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

.PHONY : clean

clean: 
	-rm *.o $(PROGRAM)
