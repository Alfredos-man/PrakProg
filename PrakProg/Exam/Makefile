CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

TARGET = main
OBJS = main.o rank.o

all: $(TARGET) out.txt

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

out.txt: $(TARGET)
	./$(TARGET) > Out.txt
	rm *.o

main.o: main.cpp rank.h
	$(CXX) $(CXXFLAGS) -c main.cpp

rank.o: rank.cpp rank.h
	$(CXX) $(CXXFLAGS) -c rank.cpp

clean:
	rm -f Out.txt $(OBJS) $(TARGET)