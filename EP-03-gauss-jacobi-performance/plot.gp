#!/usr/bin/gnuplot -c
## set encoding iso_8859_15
reset
set encoding utf

#set terminal qt persist
set grid
set style data point
set datafile separator ","
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set key outside
set key right top
set xtics

set xlabel "N (Bytes)"

set logscale y

# 1,     2,           3,       4,       5,        6,         7,         8,              9,              10              11
# n, time_normal, time_opt, L3_normal, L3_opt, L2_normal, L2_opt, FLOPS_DP_normal, FLOPS_DP_opt, FLOPS_AVX_normal, FLOPS_AVX_opt

#
# Tempos
#
set ylabel "T (seg)"
set title "Tempos de execução"
set terminal qt 0 persist title "Tempos de execução"
#set terminal png
#set output "teste.png"
plot 'dados.csv' using 1:2 title "<tempo>" lc rgb "green" with linespoints, \
    '' using 1:3 title "<tempo opt>" lc rgb "red" with linespoints

set logscale y
#
# L3 - Banda de Memória
#
set title "Banda de Memória"
set ylabel "MFLOPS/s"
set terminal qt 1 title "Banda de Memória"
plot 'dados.csv' using 1:4 title "<L3-normal>" lc rgb "green" with linespoints, \
    '' using 1:5 title "<L3-opt>" lc rgb "red" with linespoints,

# 1,     2,           3,       4,       5,        6,         7,         8,              9,              10              11
# n, time_normal, time_opt, L3_normal, L3_opt, L2_normal, L2_opt, FLOPS_DP_normal, FLOPS_DP_opt, FLOPS_AVX_normal, FLOPS_AVX_opt

#
# L2 
#
unset logscale
set title "Cache Miss L2"
set ylabel "Cache Miss Ratio"
set terminal qt 2 title "Cache Miss Ratio"
plot 'dados.csv' using 1:6 title "<L2 normal>" lc rgb "blue" with linespoint, \
    '' using 1:7 title "<L2 opt>" lc rgb "red" with linespoint

#
# FLOPS 
#
set title "Operações Aritméticas"
set ylabel "MFLOP/s"
set terminal qt 3 title "Operações Aritméticas"
plot 'dados.csv' using 1:8 title "<FLOPS DP normal>" lc rgb "green" with linespoint, \
    '' using 1:9 title "<FLOPS DP opt>" lc rgb "blue" with linespoint, \
    '' using 1:10 title "<FLOPS AVX normal>" lc rgb "red" with linespoint, \
    '' using 1:11 title "<FLOPS AVX optS>" lc rgb "pink" with linespoint
