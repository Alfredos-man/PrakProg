\
		set terminal png size 900,600; \
		set output 'opgaveC.png'; \
		set xlabel 'N'; \
		set ylabel 'time (s)'; \
		set title 'EVD runtime'; \
		set grid; \
		a = 1e-8; \
		plot 'times.out' using 1:2 with linespoints pt 7 title 'measured', \
		     a*x**3 with lines title 'a*N^3'; \
	