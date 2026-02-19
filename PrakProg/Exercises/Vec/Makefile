CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lm
TARGET = main

Out.txt: $(TARGET)
	./$(TARGET) > Out.txt
	cat Out.txt

main: $(TARGET).o vec.o
	$(CXX) -o $(TARGET) $(TARGET).o vec.o $(LDLIBS)

$(TARGET).o: $(TARGET).cpp vec.h
	$(CXX) $(CXXFLAGS) -c $(TARGET).cpp -o $(TARGET).o

vec.o: vec.cpp vec.h
	$(CXX) $(CXXFLAGS) -c vec.cpp -o vec.o

clean:
	rm -f $(TARGET) $(TARGET).o vec.o
