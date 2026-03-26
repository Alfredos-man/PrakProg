CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

all: fig1.png fig2.png fig3.png

fig1.png: fig1.gnu erf.data erf_table.data
	gnuplot $<

fig2.png: fig2.gnu gamma.data gamma_table.data
	gnuplot $<

fig3.png: fig3.gnu lngamma.data lngamma_table.data
	gnuplot $<

main: main.cpp funcs.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp funcs.cpp $(LDLIBS)

erf.data: main Makefile
	./main -func erf > $@

gamma.data: main Makefile
	./main -func sgamma -xmin 0 -xmax 5 > $@

lngamma.data: main Makefile
	./main -func lngamma -xmin 0 -xmax 8 > $@

.PHONY: clean
clean:
	rm -f main erf.data gamma.data lngamma.data fig1.png fig2.png fig3.png