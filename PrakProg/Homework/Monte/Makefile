CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = main
OBJS = main.o mcarlo.o

all: $(TARGET) opgaveA opgaveB run

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp mcarlo.h
	$(CXX) $(CXXFLAGS) -c main.cpp

mcarlo.o: mcarlo.cpp mcarlo.h
	$(CXX) $(CXXFLAGS) -c mcarlo.cpp

opgaveA: $(TARGET)
	./$(TARGET) -plotA
	gnuplot -e "\
	set terminal pngcairo size 1200,800; \
	set output 'opgaveA.png'; \
	set title 'Opgave A'; \
	set logscale xy; \
	set xlabel 'N'; \
	set ylabel 'Error'; \
	set grid; \
	plot 'opgAplot.data' using 1:2 with linespoints title 'Estimated error (1/sqrt(N))', \
	     'opgAplot.data' using 1:3 with linespoints title 'Actual error'"

opgaveB: $(TARGET)
	./$(TARGET) -plotB
	gnuplot -e "\
	set terminal pngcairo size 1200,800; \
	set output 'opgaveB.png'; \
	set title 'Opgave B'; \
	set logscale xy; \
	set xlabel 'N'; \
	set ylabel 'Actual error'; \
	set grid; \
	plot 'opgBplot.data' using 1:2 with linespoints title 'LCG', \
	     'opgBplot.data' using 1:3 with linespoints title 'std::mt19937', \
	     'opgBplot.data' using 1:4 with linespoints title 'Halton'"

run:
	./$(TARGET) -all > Out.txt
	rm *.o

clean:
	rm -f $(OBJS) $(TARGET) opgAplot.data opgBplot.data opgaveA.png opgaveB.png Out.txt