#!/bin/bash

#Ns="1 1000"
Ns="1 2 3 5 8 13 21 34"

slFile="sl.txt"
tmpFile="tmp.txt"
resultadosFile="dados.csv"
geraSLFile="./geraSL"

tests="L2CACHE L3 FLOPS_DP"

kernel=1
# Compila geraSL.c

rm $tmpFile &>/dev/null
rm $slFile &>/dev/null
rm $resultadosFile &>/dev/null



if [[ ! -f $geraSLFile ]]; then
    echo "O arquivo $geraSLFile não existe"
    exit 0;
fi

echo "n, time_normal, time_opt, L3_normal, L3_opt, L2_normal, L2_opt, FLOPS_DP_normal, FLOPS_DP_opt, FLOPS_AVX_normal, FLOPS_AVX_opt" > $resultadosFile

# geraSL n >> sl.txt
for n in $Ns;
do 
    echo -n "$n," >> $resultadosFile

    $geraSLFile $n > $slFile


    # --- RODA ANOTANDO L3
    likwid-perfctr -C 1 -g L3 -O -m ./gaussJacobi-likwid $slFile > $tmpFile

    cat  $tmpFile | grep '^Runtime (RD*' | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile

    cat  $tmpFile | grep "L3 bandwidth" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile


    # --- RODA ANOTANDO L2
    likwid-perfctr -C 1 -g L2CACHE -O -m ./gaussJacobi-likwid $slFile > $tmpFile

    cat  $tmpFile | grep "L2 miss ratio" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile


    # --- RODA ANOTANDO FLOPS
    likwid-perfctr -C 1 -g FLOPS_DP -O -m ./gaussJacobi-likwid $slFile > $tmpFile

    cat  $tmpFile | grep '^DP [MFLOP/s]*' | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile
    cat  $tmpFile | grep "AVX DP" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile

    echo "" >> $resultadosFile



    #echo "Gerado SL $n ";
done


# done

# Rodar gaussJacobi olhando para L2CACHE    para sl.txt
# Rodar gaussJacobi olhando para FLOPS_DP   para sl.txt
# Rodar gaussJacobiOpt olhando para etcetc  para sl.txt (*3)