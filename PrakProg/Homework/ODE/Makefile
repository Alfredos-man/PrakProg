CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
TARGET = main

all: main opgaveA


main: main.cpp ODE.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp ODE.cpp

opgaveA: $(TARGET)
	./$(TARGET) > opgA.data
	gnuplot -e "\
	set terminal pngcairo size 1000,700; \
	set output 'opgA.png'; \
	set grid; \
	set title 'ODE løsning'; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	plot 'opgA.data' using 1:2 with lines lw 2 title 'Numerisk løsning'"

clean:
	rm -f *.txt *.data *.png main