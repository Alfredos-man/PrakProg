CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

TARGET = main

all: $(TARGET) run-a run-b

$(TARGET): main.o ann.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o ann.o

main.o: main.cpp ann.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ann.o: ann.cpp ann.h
	$(CXX) $(CXXFLAGS) -c ann.cpp

run-a: $(TARGET)
	./$(TARGET) A
	gnuplot -e "set terminal pngcairo; \
	            set output 'opgaveA.png'; \
	plot 'data_a.txt' using 1:2 with lines dt 2 lw 2 title 'Exact', \
	     'data_a.txt' using 1:3 with lines dt 1 lw 2 title 'ANN'"

run-b: $(TARGET)
	./$(TARGET) B
	gnuplot -e "set terminal pngcairo; \
	            set output 'opgaveB.png'; \
	plot 'data_b.txt' using 1:2 with lines dt 2 lw 2 title 'Exact', \
	     'data_b.txt' using 1:3 with lines dt 1 lw 2 title 'ANN', \
	     'data_b.txt' using 1:4 with lines dt 1 lw 2 title 'Exact derivative', \
	     'data_b.txt' using 1:5 with lines dt 2 lw 2 title 'ANN derivative'"

clean:
	rm -f *.o $(TARGET) *.png data_*.txt