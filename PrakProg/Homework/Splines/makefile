CXX = clang++
CXXFLAGS = -Wall -std=c++11

TARGET = main
SRC = main.cpp interp.cpp quadspline.cpp cubespline.cpp

all: opgaveA opgaveB opgaveC

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

opgaveA: $(TARGET)
	./$(TARGET) -opgaveA > opgaveA.data
	gnuplot -e "set terminal png; \
	set output 'opgaveA.png'; \
	set title 'Linear Interpolation'; \
	set xlabel 'z'; \
	set ylabel 'Value'; \
	plot 'opgaveA.data' using 1:2 with lines title 'interp(z)', \
	     'opgaveA.data' using 1:3 with lines title 'integral(z)'"
	

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
	

opgaveC: $(TARGET)
	./$(TARGET) -opgaveC > opgaveC.data
	gnuplot -e 'set terminal pngcairo; \
	set output "opgaveC.png"; \
	set title "Cubic spline for cos(x)"; \
	set xlabel "z"; \
	set ylabel "value"; \
	set grid; \
	plot "opgaveC.data" using 1:2 with lines title "cos(z)", \
	     "opgaveC.data" using 1:3 with lines title "cubic spline", \
	     "opgaveC.data" using 1:5 with lines title "cubic integral"'
	

Out.txt: $(TARGET)
	./$(TARGET) > Out.txt
	cat Out.txt

clean:
	rm -f *.o *.png *.data $(TARGET) Out.txt