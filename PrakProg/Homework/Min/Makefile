CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = main

SRC = main.cpp newton.cpp QR.cpp
OBJ = $(SRC:.cpp=.o)

all: run

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	rm -f $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.txt $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET) > Out.txt