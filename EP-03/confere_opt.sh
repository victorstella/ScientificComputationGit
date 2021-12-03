#!/bin/bash

#Ns="1 1000"
#Ns="10 32 50 64"
Ns="10 32 50 64 100 128 200 250 256 300 400 512 600 1000 1024 2000 2048 3000 4096"

slFile="sl.txt"
tmpFile="tmp.txt"
resultadosFile="dados.csv"

executFile="./gaussJacobi-likwid"
geraSLFile="./geraSL"

tests="L2CACHE L3 FLOPS_DP"

kernel=1
# Compila geraSL.c

rm $tmpFile &>/dev/null
rm $slFile &>/dev/null
rm $resultadosFile &>/dev/null



if [[ ! -f $geraSLFile ]]; then
    echo "O arquivo $geraSLFile não existe"
    echo "Compilando..."
    gcc geraSL.c -lm -o $geraSLFile
    echo "Compilado!"
fi

if [[ ! -f $executFile ]]; then
    echo "Arquivo $executFile não existe"
    echo "Compilando..."
    make
    echo "Compilado!"
fi

echo "n, time_normal, time_opt, L3_normal, L3_opt, L2_normal, L2_opt, FLOPS_DP_normal, FLOPS_DP_opt, FLOPS_AVX_normal, FLOPS_AVX_opt" > $resultadosFile

# geraSL n >> sl.txt
for n in $Ns;
do 
    echo -n "$n," >> $resultadosFile

    $geraSLFile $n > $slFile


    # --- RODA ANOTANDO L3
    likwid-perfctr -C 1 -g L3 -O -m $executFile $slFile > L3_$n$tmpFile

    cat  L3_$n$tmpFile | grep '^Runtime (RD*' | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile

    cat  L3_$n$tmpFile | grep "L3 bandwidth" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile


    # --- RODA ANOTANDO L2
    likwid-perfctr -C 1 -g L2CACHE -O -m $executFile $slFile > L2_$n$tmpFile

    cat  L2_$n$tmpFile | grep "L2 miss ratio" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile


    # --- RODA ANOTANDO FLOPS
    likwid-perfctr -C 1 -g FLOPS_DP -O -m $executFile $slFile > FLOPS_$n$tmpFile

    cat  FLOPS_$n$tmpFile | grep '^DP [MFLOP/s]*' | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile
    cat  FLOPS_$n$tmpFile | grep "AVX DP" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile

    echo "" >> $resultadosFile



    #echo "Gerado SL $n ";
done


# done

# Rodar gaussJacobi olhando para L2CACHE    para sl.txt
# Rodar gaussJacobi olhando para FLOPS_DP   para sl.txt
# Rodar gaussJacobiOpt olhando para etcetc  para sl.txt (*3)