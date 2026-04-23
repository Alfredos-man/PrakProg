CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = program
SRC = main.cpp jakobi.cpp

RMAX = 10
DR = 0.2

all: plot

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

out.dat: $(TARGET)
	./$(TARGET) $(RMAX) $(DR) > out.dat

plot: out.dat opgaveB.gnu
	gnuplot opgaveB.gnu

clean:
	rm -f $(TARGET) out.dat wave.png