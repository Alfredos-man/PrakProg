CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = main
SOURCES = main.cpp QR.cpp newton.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET) opgave1 opgave2

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

opgave1: main
	./main -opgave1 > Out.txt

opgave2: main
	./main -opgave2
	gnuplot -e '\
	set terminal pngcairo size 1200,800; \
	set output "Opg2.png"; \
	set title "Hydrogen wavefunction"; \
	set xlabel "r"; \
	set ylabel "f(r)"; \
	set grid; \
	plot "wavefunction.txt" using 1:2 with lines lw 2 title "Numerical", \
	     "wavefunction.txt" using 1:3 with lines lw 2 title "Exact"; \
	set output'
	rm *.o wavefunction.txt



clean:
	rm -f *.txt *.png $(OBJECTS) $(TARGET)
