#include "functions.h"

//void **funcs; // Array de funções em forma de ponteiros para void e a matriz jacobiana seguindo a mesma estrutura com 1 dimensão a mais



// Lê e trata as entradas
int inputs (sl_t sl) {

    // 

}




// Retorna o maior entre 2 valores
double maior(double x, double y) {
    double a, b;
    a = fabs(x);
    b = fabs(y);

    if (a > b) return a;
    else if (b > a) return b;
    else return a;
}

