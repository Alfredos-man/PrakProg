CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lm
TARGET = main

Out.txt: $(TARGET)
	./$(TARGET) > Out.txt
	cat Out.txt

main: $(TARGET).o
	$(CXX) -o $(TARGET) $(TARGET).o $(LDLIBS)

$(TARGET).o: $(TARGET).cpp vec.h
	$(CXX) $(CXXFLAGS) -c $(TARGET).cpp -o $(TARGET).o

clean:
	rm -f $(TARGET) $(TARGET).o Out.txt