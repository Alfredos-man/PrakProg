set terminal pngcairo size 800,600
set output 'wave.png'

set xlabel 'r'
set ylabel 'u(r)'
set title 'Hydrogen radial wavefunctions'

plot 'out.dat' using 1:2 with lines title 'num 1s', \
     'out.dat' using 1:3 with lines title 'ana 1s', \
     'out.dat' using 1:4 with lines title 'num 2s', \
     'out.dat' using 1:5 with lines title 'ana 2s', \
     'out.dat' using 1:6 with lines title 'num 3s', \
     'out.dat' using 1:7 with lines title 'ana 3s'