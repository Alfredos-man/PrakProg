CXX = clang++
CXXFLAGS = -Wall -std=c++11

TARGET = main
SRC = main.cpp interp.cpp quadspline.cpp

all: Out.txt interplot

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

opgaveA: 
	./$(TARGET) -opgaveA > inter.data
	gnuplot -e "set terminal png; \
	set output 'OpgA.png'; \
	set title 'Linear Interpolation'; \
	set xlabel 'z'; \
	set ylabel 'Value'; \
	plot 'inter.data' using 1:2 with lines title 'interp(z)', \
	     'inter.data' using 1:3 with lines title 'integral(z)'"

opgaveB: $(TARGET)
	./$(TARGET) -opgaveB > opgaveB.data
	gnuplot -e 'set terminal pngcairo; \
	set output "opgaveB.png"; \
	set title "Quadratic spline for cos(x)"; \
	set xlabel "z"; \
	set ylabel "value"; \
	set grid; \
	plot "opgaveB.data" using 1:2 with lines title "cos(z)", \
	     "opgaveB.data" using 1:5 with dots title "quadratic spline", \
	     "opgaveB.data" using 1:7 with lines title "quadratic integral"'


Out.txt: $(TARGET)
	./$(TARGET) > Out.txt
	cat Out.txt

clean:
	rm -f *.o *.png $(TARGET) Out.txt