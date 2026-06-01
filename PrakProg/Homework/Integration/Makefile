CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

main: main.o Quad.o
	$(CXX) $(CXXFLAGS) -o main main.o Quad.o

main.o: main.cpp Quad.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Quad.o: Quad.cpp Quad.h
	$(CXX) $(CXXFLAGS) -c Quad.cpp


plot.png: erf_accuracy.txt
	gnuplot -e "\
	set terminal png size 800,600; \
	set output 'plot.png'; \
	set logscale xy; \
	set xlabel 'acc'; \
	set ylabel '|erf(1)-exact|'; \
	set title 'Adaptive quadrature accuracy'; \
	set grid; \
	plot 'erf_accuracy.txt' using 1:2 with linespoints"

clean:
	rm -f *.o main