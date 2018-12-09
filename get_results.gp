plot "get_results.csv" with linespoints title "Time (ms) per GET"
set title "Average time per GET Request"
set ylabel "Time (ms)"
set xlabel "Requests Per Second"
set title "Time (ms) per GET at n Requests per Second"  
set logscale x 2
replot
