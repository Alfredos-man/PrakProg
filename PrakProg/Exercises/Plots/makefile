CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

all: fig1.svg fig2.svg fig3.svg

fig1.svg: fig1.gnu erf.data erf_table.data
	gnuplot $<

fig2.svg: fig2.gnu gamma.data gamma_table.data
	gnuplot $<

fig3.svg: fig3.gnu lngamma.data lngamma_table.data
	gnuplot $<

main: main.cpp funcs.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp funcs.cpp $(LDLIBS)

erf.data: main Makefile
	./main > $@

gamma.data: main Makefile
	./main -xmin 0 -xmax 3 > $@

lngamma.data: main Makefile
	./main -xmin 0 -xmax 3 -log > $@

.PHONY: clean
clean:
	rm -f main erf.data gamma.data lngamma.data fig1.png fig2.png fig3.png