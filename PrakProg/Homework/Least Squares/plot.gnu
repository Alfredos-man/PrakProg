set terminal pngcairo size 1000,700
set output "Plot.png"

set xlabel "Time t (days)"
set ylabel "Activity y (relative units)"
set title "Radioactive decay of ThX / Ra-224"

plot \
    "data.txt" using 1:2:3 with yerrorbars title "Experimental data", \
    "fit.txt" using 1:2 with lines title "Best fit"