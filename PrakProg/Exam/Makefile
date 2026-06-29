CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

TARGET = main
OBJS   = main.o rank.o


all: $(TARGET) run plot

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp rank.h
	@$(CXX) $(CXXFLAGS) -c $<

rank.o: rank.cpp rank.h
	@$(CXX) $(CXXFLAGS) -c $<

run: $(TARGET)
	@./$(TARGET) -tests > Out.txt
	./$(TARGET) -plot


plot: benchmark.data
	@gnuplot -e "\
	set fit quiet; \
	set terminal pngcairo size 800,600; \
	set output 'benchmark.png'; \
	set xlabel 'Matrixstørrelse n'; \
	set ylabel 'Tid (ms)'; \
	set title 'Rank-1 Eigenvalue Solver'; \
	set grid; \
	f(x)=a*x*x; \
	fit f(x) 'benchmark.data' using 1:2 via a; \
	plot \
	    'benchmark.data' using 1:2 with linespoints lw 2 title 'Målt tid', \
	    f(x) lw 2 title sprintf('%.3e*n^2',a)"
	

clean:
	@rm -f $(TARGET) $(OBJS) benchmark.data benchmark.png fit.log Out.txt