set terminal pngcairo size 800,600 enhanced
set output "fig2.png"
plot "gamma.data" with lines, "gamma_table.data" with points