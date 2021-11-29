#!/bin/bash

Ns="1 1 2 3 5 8 13 21 34"

slFile="sl.txt"

# Compila geraSL.c


rm $slFile;

# geraSL n >> sl.txt
for n in $Ns;
do 
    ./geraSL $n >> $slFile;
    echo -e "\n\n" >> $slFile; 

    # teste pra L3
        # em GaussJacobi
        # em GaussJacobiOpt
    # teste pra L2CACHE
    # teste pra FLOPS
    echo "Gerado SL $n ";
done

# Rodar gaussJacobi olhando para L3         para sl.txt
# Rodar gaussJacobi olhando para L2CACHE    para sl.txt
# Rodar gaussJacobi olhando para FLOPS_DP   para sl.txt
# Rodar gaussJacobiOpt olhando para etcetc  para sl.txt (*3)