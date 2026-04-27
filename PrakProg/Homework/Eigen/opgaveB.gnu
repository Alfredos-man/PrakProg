set terminal pngcairo size 1200,800
set output 'wave.png'

set title 'Hydrogen radial wavefunctions'
set xlabel 'r'
set ylabel 'u(r)'
set grid
set key top right
set xrange [0:10]

plot 'out.dat' using 1:2 with lines lw 3 dt 1 title 'numerical 1s', \
     'out.dat' using 1:3 with lines lw 3 dt 2 title 'analytical 1s', \
     'out.dat' using 1:4 with lines lw 3 dt 1 title 'numerical 2s', \
     'out.dat' using 1:5 with lines lw 3 dt 2 title 'analytical 2s', \
     'out.dat' using 1:6 with lines lw 3 dt 1 title 'numerical 3s', \
     'out.dat' using 1:7 with lines lw 3 dt 2 title 'analytical 3s'