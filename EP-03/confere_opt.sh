#!/bin/bash

Ns="1 1 2 3 5 8 13 21 34"

slFile="sl.txt"

tests="L2CACHE L3 FLOPS_DP"

kernel=1
# Compila geraSL.c

rm sl-*.txt &>/dev/null

# geraSL n >> sl.txt
for n in $Ns;
do 
    ./geraSL $n > tmp-$n.txt

    cat tmp-$n.txt | grep "L3 bandwidth" | cut -d',' -f3 >> L3-"$n".txt
    cat tmp-$n.txt | grep "Runtime (RDTSC)" | cut -d',' -f3 >> sl-"$n".txt

    echo -e "\n\n" >> $slFile; 

    # teste pra L3
        # em GaussJacobi
        # em GaussJacobiOpt
    # teste pra L2CACHE
    # teste pra FLOPS
    echo "Gerado SL $n ";
done

# for n in Ns
    #L3:
        #likwid-perfctr -C 1 -g FLOPS_DP -O -m ./gaussJacobi-likwid sl.txt
            # ^^  Rodar gaussJacobi-likwid olhando para L3      para sl.txt > temp.csv
        # grep temp.csv >> results.csv

    #L2:
        #...
        
    #Flops:
        #...

# done

# Rodar gaussJacobi olhando para L2CACHE    para sl.txt
# Rodar gaussJacobi olhando para FLOPS_DP   para sl.txt
# Rodar gaussJacobiOpt olhando para etcetc  para sl.txt (*3)