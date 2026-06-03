CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = main
SOURCES = main.cpp QR.cpp newton.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.txt $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)