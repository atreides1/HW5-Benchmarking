plot "adj_and_avg_get.csv" using 1:2 with linespoints title "Average Time per GET Request", "adj_and_avg_get.csv" using 1:3 with linespoints title "Adjusted Time per GET Request", 1 title "1 ms"
set ylabel "Time (ms)"
set xlabel "Requests per Second"
set title "Time (ms) per Average and Adjusted GET at n Requests per Second" 
set logscale x 2
replot
set output "adj_and_avg_get.png"
