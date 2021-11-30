#!/usr/bin/gnuplot -c
## set encoding iso_8859_15
set encoding utf

#set terminal qt persist
set grid
set style data point
set datafile separator ","
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set xtics
#set xrange [64:5000]
set xlabel "N (Bytes)"

# set logscale x
set logscale y

# 1,  2,       3,       4,       5,        6,          7,              8,              9,              10
# n, time, L3_normal, L3_opt, L2_normal, L2_opt, FLOPS_DP_normal, FLOPS_DP_opt, FLOPS_AVX_normal, FLOPS_AVX_opt



#
# Tempos
#
set ylabel "T (seg)"
set title "Tempos de execução"
set terminal qt 1 title "Tempos de execução"
#set terminal png
#set output "teste.png"
plot 'dados.csv' using 1:2 title "<tempo>" lc rgb "green" with linespoints

#
# FLOPS
#
#set ylabel "MFLOPS/s"
#set title "FLOPS DP e AVX"
#set terminal qt 1 title "FLOPS DP e AVX"
#plot 'FLOPS_DP.csv' using 1:3 title "<O3+AVX>" lc rgb "green" with linespoints, \
#    '' using 1:2 title "<O3+DP>" lc rgb "blue" with linespoints, \
#    '' using 1:4 title "<sem Otimiz>" lc rgb "red" with linespoints, \
