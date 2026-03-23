set terminal pngcairo size 800,600 enhanced
set output "fig3.png"
plot "lngamma.data" with lines, "lngamma_table.data" with points