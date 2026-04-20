CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = program
SRC = main.cpp jakobi.cpp

all: Out.txt

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

Out.txt: $(TARGET)
	./$(TARGET) > Out.txt

clean:
	rm -f $(TARGET) Out.txt
	