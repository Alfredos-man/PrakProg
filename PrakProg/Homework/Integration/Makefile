CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

all: main output plotA plotC cleanup

main: main.cpp Quad.cpp Quad.h
	$(CXX) $(CXXFLAGS) main.cpp Quad.cpp -o main

output: main
	./main > Out.txt

plots: main
	./main

plotA: plots
	gnuplot -e "\
	set terminal pngcairo size 800,600; \
	set output 'OpgA.png'; \
	set logscale xy; \
	set xlabel 'acc'; \
	set ylabel '|erf(1)-exact|'; \
	set title 'Adaptive quadrature accuracy'; \
	set grid; \
	plot 'erf_accuracy.txt' using 1:2 with linespoints lw 2 title 'erf error'"

plotC: plots
	gnuplot -e "\
	set terminal pngcairo size 1000,700; \
	set output 'OpgC.png'; \
	set logscale xy; \
	set grid; \
	set xlabel 'Requested accuracy'; \
	set ylabel 'Error'; \
	set title 'Estimated vs actual integration error'; \
	plot \
	'error_estimate.txt' using 1:2 with linespoints lw 2 title 'estimated', \
	'error_estimate.txt' using 1:3 with linespoints lw 2 title 'actual'"

cleanup: 
	rm erf_accuracy.txt error_estimate.txt

clean:
	rm -f main *.o *.txt *.png Out.txt