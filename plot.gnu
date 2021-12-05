set term png size 1900,1000

set output "plot.png"

set grid

set ylabel "Latency in cycles"

set xlabel "Array size"

plot "result.dat" u 2:1 t "Pearson Correlation" w lp