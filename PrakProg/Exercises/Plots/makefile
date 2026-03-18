CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = plots.cpp

SRC = main.cpp plots.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp plots.h
erf.o: plots.cpp plots.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)