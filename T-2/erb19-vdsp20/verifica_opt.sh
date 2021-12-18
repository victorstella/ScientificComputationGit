
# -- Arquivos
sl_file="sl.txt"
tmp_file="tmp.txt"
resultados_file="dados.csv"
# -- Arquivos executáveis
exe_newton_snl="./newtonSNL"
sh_broyden="./broyden.sh"
snl_broyden="./broyden.dat"

# Exclui arquivos caso existam 
rm $tmp_file &>/dev/null
rm $slFile &>/dev/null
rm $resultados_file &>/dev/null

# Compila gerador de sistemas lineares caso não esteja compilado
if [[ ! -f $snl_broyden ]]; then
    echo "O arquivo $sh_bsnl_broydenroyden não existe"
    echo "Gerando broyden..."
    $sh_broyden
    echo "Gerado!"
fi

# Compila solucionador de sistemas lineares
if [[ ! -f $exe_newton_snl ]]; then
    echo "Arquivo $exe_newton_snl não existe"
    echo "Compilando..."
    make avx
    echo "Compilado!"
fi


# Cabeçalho de arquivo csv 
echo "m, time_derivadas, L3_derivadas, L2_derivadas, FLOPS_DP_derivadas, time_newton, L3_newton, L2_newton, FLOPS_DP_newton, time_jacobi, L3_jacobi, L2_jacobi, FLOPS_DP_jacobi, time_sl, L3_sl, L2_sl, FLOPS_DP_sl,"


echo -n "Obtendo informações de sistema linear de tamanho $n... "

echo -n "$n," >> $resultados_file

# Cria sistema linear de tamanho n em $slFile
$exeGeraSL $n > $slFile

# --- RODA PROGRAMA ANOTANDO L3 ---
likwid-perfctr -C 1 -g L3 -O -m $exe_newton_snl < $sl_file > $tmp_file

# Anota tempo de execução ---
cat  $tmp_file | grep '^Runtime (RD*' | cut -d',' -f2 | tr '\n' ',' >> $resultados_file

# Anota L3 Bandwith
cat  $tmp_file | grep "L3 bandwidth" | cut -d',' -f2 | tr '\n' ',' >> $resultados_file


# --- RODA PROGRAMA ANOTANDO L2 ---
likwid-perfctr -C 1 -g L2CACHE -O -m $exe_newton_snl < $sl_file > $tmp_file

# Anota miss ratio de L2
cat  $tmp_file | grep "L2 miss ratio" | cut -d',' -f2 | tr '\n' ',' >> $resultados_file


# --- RODA PROGRAMA ANOTANDO FLOPS ---
likwid-perfctr -C 1 -g FLOPS_DP -O -m $exe_newton_snl < $sl_file > $tmp_file

# Anota FLOPS_DP
cat  $tmp_file | grep '^DP [MFLOP/s]*' | cut -d',' -f2 | tr '\n' ',' >> $resultados_file

# Anota FLOPS_DP AVX
cat  $tmp_file | grep "AVX DP" | cut -d',' -f2 | tr '\n' ',' >> $resultados_file

echo "" >> $resultados_file

echo " Pronto!"
