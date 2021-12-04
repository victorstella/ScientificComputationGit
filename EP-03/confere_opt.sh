#!/bin/bash

#Ns="1 1000"
#Ns="10 32 50 64"
Ns="10 32 50 64 100 128 200 250 256 300 400 512 600 1000 1024 2000 2048 3000 4096"

# -- Arquivos
slFile="sl.txt"
tmpFile="tmp.txt"
resultadosFile="dados.csv"
# -- Arquivos executáveis
exeGaussJacobi="./gaussJacobi-likwid"
exeGeraSL="./geraSL"

# Exclui arquivos caso existam 
rm $tmpFile &>/dev/null
rm $slFile &>/dev/null
rm $resultadosFile &>/dev/null

# Compila gerador de sistemas lineares caso não esteja compilado
if [[ ! -f $exeGeraSL ]]; then
    echo "O arquivo $exeGeraSL não existe"
    echo "Compilando..."
    gcc geraSL.c -lm -o $exeGeraSL
    echo "Compilado!"
fi

# Compila solucionador de sistemas lineares
if [[ ! -f $exeGaussJacobi ]]; then
    echo "Arquivo $exeGaussJacobi não existe"
    echo "Compilando..."
    make avx
    echo "Compilado!"
fi

# Cabeçalho de arquivo csv
echo "n, time_normal, time_opt, L3_normal, L3_opt, L2_normal, L2_opt, FLOPS_DP_normal, FLOPS_DP_opt, FLOPS_AVX_normal, FLOPS_AVX_opt" > $resultadosFile

for n in $Ns;
do
    echo -n "Obtendo informações de sistema linear de tamanho $n... "

    echo -n "$n," >> $resultadosFile

    # Cria sistema linear de tamanho n em $slFile
    $exeGeraSL $n > $slFile

    # --- RODA PROGRAMA ANOTANDO L3 ---
    likwid-perfctr -C 1 -g L3 -O -m $exeGaussJacobi $slFile > L3_$n$tmpFile

    # Anota tempo de execução ---
    cat  L3_$n$tmpFile | grep '^Runtime (RD*' | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile

    # Anota L3 Bandwith
    cat  L3_$n$tmpFile | grep "L3 bandwidth" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile


    # --- RODA PROGRAMA ANOTANDO L2 ---
    likwid-perfctr -C 1 -g L2CACHE -O -m $exeGaussJacobi $slFile > L2_$n$tmpFile

    # Anota miss ratio de L2
    cat  L2_$n$tmpFile | grep "L2 miss ratio" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile


    # --- RODA PROGRAMA ANOTANDO FLOPS ---
    likwid-perfctr -C 1 -g FLOPS_DP -O -m $exeGaussJacobi $slFile > FLOPS_$n$tmpFile

    # Anota FLOPS_DP
    cat  FLOPS_$n$tmpFile | grep '^DP [MFLOP/s]*' | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile

    # Anota FLOPS_DP AVX
    cat  FLOPS_$n$tmpFile | grep "AVX DP" | cut -d',' -f2 | tr '\n' ',' >> $resultadosFile

    echo "" >> $resultadosFile

    echo " Pronto!"
done
