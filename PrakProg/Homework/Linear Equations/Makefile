CXX      = c++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2
OBJS     = main.o QR.o

.NOTPARALLEL:
.PHONY: all clean

all: plot.png out.txt

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

times.out: main
	@tmp=$@.tmp; \
	rm -f $$tmp; \
	for N in $$(seq 100 20 1500); do \
		T=$$({ /usr/bin/time -p ./main $$N > /dev/null; } 2>&1 | awk '/^real/ {print $$2}'); \
		echo "$$N $$T" >> $$tmp; \
	done; \
	mv $$tmp $@

plot.png: times.out
	gnuplot -e "\
		set terminal png size 900,600; \
		set output '$@'; \
		set xlabel 'N'; \
		set ylabel 'time (s)'; \
		set title 'QR factorization runtime'; \
		set grid; \
		a = 1e-9; \
		plot 'times.out' using 1:2 with linespoints pt 7 title 'measured', \
		     a*x**3 with lines title 'a*N^3'; \
	"

out.txt: main
	./main > out.txt

main.o: main.cc matrix.h QR.h
QR.o: QR.cc QR.h matrix.h

clean:
	rm -f main *.o times.out fit.log out