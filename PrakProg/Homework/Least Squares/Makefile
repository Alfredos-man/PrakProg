CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = main
SRC = main.cpp lsfit.cpp QR.cpp

all: Out.txt Plot.png

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

Out.txt: $(TARGET)
	./$(TARGET) > Out.txt

Plot.png:
	gnuplot plot.gnu
	rm data.txt fit.txt

clean:
	rm -f $(TARGET) Out.txt Plot.png