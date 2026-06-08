CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
TARGET = main

all: main opgaveA opgaveB1 opgaveB2 opgaveB3 plotB


main: main.cpp ODE.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp ODE.cpp

opgaveA: $(TARGET)
	./$(TARGET) -opgaveA > opgA.data
	gnuplot -e "\
	set terminal pngcairo size 1000,700; \
	set output 'opgA.png'; \
	set grid; \
	set title 'ODE løsning'; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	plot 'opgA.data' using 1:2 with lines lw 2 title 'Numerisk løsning'"


opgaveB1: $(TARGET)
	./$(TARGET) -opgaveB 1 > opgaveB1.data
	gnuplot -e "\
	set terminal pngcairo size 1000,1000; \
	set output 'opgaveB1.png'; \
	set size ratio -1; \
	plot 'opgaveB1.data' using (cos(\$$1)/\$$2):(sin(\$$1)/\$$2) \
	with lines notitle"

opgaveB2: $(TARGET)
	./$(TARGET) -opgaveB 2 > opgaveB2.data
	gnuplot -e "\
	set terminal pngcairo size 1000,1000; \
	set output 'opgaveB2.png'; \
	set size ratio -1; \
	plot 'opgaveB2.data' using (cos(\$$1)/\$$2):(sin(\$$1)/\$$2) \
	with lines notitle"

opgaveB3: $(TARGET)
	./$(TARGET) -opgaveB 3 > opgaveB3.data
	gnuplot -e "\
	set terminal pngcairo size 1000,1000; \
	set output 'opgaveB3.png'; \
	set size ratio -1; \
	plot 'opgaveB3.data' using (cos(\$$1)/\$$2):(sin(\$$1)/\$$2) \
	with lines notitle"

plotB: opgaveB1 opgaveB2 opgaveB3

clean:
	rm -f *.txt *.data *.png main