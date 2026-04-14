CXX = c++
CXXFLAGS = -Wall -Werror -O -std=c++23
LDLIBS = -lm

N = 100000000000

times.png: out.times Makefile
	echo '\
		set terminal png ;\
		set output "$@" ;\
		set xlabel "Threads" ;\
		set ylabel "time (real time)" ;\
		set title "Computation, N = $(N) terms" ;\
		a = 1; b = 10 ;\
		f(x) = a + b/x ;\
		fit f(x) "$<" using 1:2 via a,b ;\
		plot \
			"$<" using 1:2 with linespoints title "times", \
			f(x) title "fit a + b/x", \
			b/x title "1/x scaled" ;\
		' | tee log.times | gnuplot

out.times: main
	> $@
	> log.main
	for nthreads in 1 2 4 8 16 32; do \
		echo "Running with $$nthreads threads"; \
		{ time ./main -terms $(N) -threads $$nthreads >> log.main; } 2> tmp.time; \
		realtime=$$(awk '/^real/ { \
			split($$2,a,"m"); \
			gsub(/s/,"",a[2]); \
			print a[1]*60 + a[2]; \
		}' tmp.time); \
		echo "$$nthreads $$realtime" >> $@; \
	done
	rm -f tmp.time

clean:
	rm -f *.o out.times log.main times.png tmp.time main