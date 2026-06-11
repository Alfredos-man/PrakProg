CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = main

SRC = main.cpp newton.cpp QR.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET) opgave1 opgave2

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

opgave1: $(TARGET)
	./$(TARGET) opgave1 > Out.txt

opgave2: $(TARGET)
	./$(TARGET) opgave2 < cern.data > fit.txt 2> log

	echo 'set terminal pngcairo size 1200,800; \
	      set output "higgs_fit.png"; \
	      set xlabel "Energy [GeV]"; \
	      set ylabel "Cross section"; \
	      set grid; \
	      plot "cern.data" using 1:2:3 with yerrorbars title "Data", \
	           "fit.txt" using 1:2 with lines lw 2 title "Fit"' \
	| gnuplot
	rm fit.txt log *.o 

clean:
	rm -f $(OBJ) $(TARGET) *.txt fit.txt *.png log 