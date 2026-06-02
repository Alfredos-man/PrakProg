CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = main
OBJS = main.o mcarlo.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp mcarlo.h
	$(CXX) $(CXXFLAGS) -c main.cpp

mcarlo.o: mcarlo.cpp mcarlo.h
	$(CXX) $(CXXFLAGS) -c mcarlo.cpp



plotA: main
	gnuplot -e "\
	set terminal pngcairo size 1200,800; \
	set output 'opgaveA.png'; \
	set title 'Monte Carlo Error'; \
	set xlabel 'N'; \
	set ylabel 'Error'; \
	set logscale xy; \
	set grid; \
	plot 'opgAplot.data' using 1:2 with linespoints title 'Estimated error', \
	     'opgAplot.data' using 1:3 with linespoints title 'Actual error', \
	     1/sqrt(x) with lines title '1/sqrt(N)'"
clean:
	rm -f *.o *.txt *.data *.png $(OBJS) $(TARGET)