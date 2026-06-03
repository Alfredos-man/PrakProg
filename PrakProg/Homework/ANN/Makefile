CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
TARGET = main


main: $(TARGET).o Ann.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).o Ann.o

main.o: main.cpp Ann.h
	$(CXX) $(CXXFLAGS) -c $(TARGET).cpp

Ann.o: Ann.cpp Ann.h
	$(CXX) $(CXXFLAGS) -c Ann.cpp

clean:
	rm -f *.o main