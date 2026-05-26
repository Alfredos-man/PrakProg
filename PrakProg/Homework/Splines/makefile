CXX = clang++
CXXFLAGS = -Wall -std=c++11

TARGET = main
SRC = main.cpp interp.cpp

all: Out.txt interplot

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

interplot: 
	./$(TARGET) > inter.data
	gnuplot -e "set terminal png; \
	set output 'plot.png'; \
	set title 'Linear Interpolation'; \
	set xlabel 'z'; \
	set ylabel 'Value'; \
	plot 'inter.data' using 1:2 with lines title 'interp(z)', \
	     'inter.data' using 1:3 with lines title 'integral(z)'"



Out.txt: $(TARGET)
	./$(TARGET) > Out.txt
	cat Out.txt

clean:
	rm -f *.o $(TARGET) Out.txt