CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

main: main.o Quad.o
	$(CXX) $(CXXFLAGS) -o main main.o Quad.o

main.o: main.cpp Quad.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Quad.o: Quad.cpp Quad.h
	$(CXX) $(CXXFLAGS) -c Quad.cpp

clean:
	rm -f *.o main