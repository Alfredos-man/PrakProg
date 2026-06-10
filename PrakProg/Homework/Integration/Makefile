CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

all: Output plot

main: main.o Quad.o
	$(CXX) $(CXXFLAGS) -o main main.o Quad.o

main.o: main.cpp Quad.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Quad.o: Quad.cpp Quad.h
	$(CXX) $(CXXFLAGS) -c Quad.cpp

Output: main
	./main > Out.txt

plot: erf_accuracy.txt
	gnuplot -e "\
	set terminal png size 800,600; \
	set output 'plot.png'; \
	set logscale xy; \
	set xlabel 'acc'; \
	set ylabel '|erf(1)-exact|'; \
	set title 'Adaptive quadrature accuracy'; \
	set grid; \
	plot 'erf_accuracy.txt' using 1:2 with linespoints"
	rm erf_accuracy.txt *.o

clean:
	rm -f *.o *.png *.txt main