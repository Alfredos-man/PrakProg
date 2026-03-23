set terminal pngcairo size 800,600 enhanced
set output "fig1.png"
plot "erf.data" with lines, "erf_table.data" with points