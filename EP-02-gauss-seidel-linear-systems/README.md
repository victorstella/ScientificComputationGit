# Banded Linear Systems — Gauss-Seidel

Solves a linear system `Ax = b` iteratively with the Gauss-Seidel method,
where `A` is stored compactly as a set of diagonals rather than a full
dense matrix.

**Authors:** Eduardo Rosso Barbosa (GRR20190378) · Victor Daniel Stella Paiva (GRR20200234)

## Theory

Gauss-Seidel is an iterative method for `Ax = b`. Solving the `i`-th
equation for `x_i` gives:

```
x_i = (b_i - sum_{j != i} A[i][j] * x_j) / A[i][i]
```

Starting from an initial guess, the method sweeps through `i = 1..n`,
recomputing each `x_i` from this formula — and, unlike Gauss-Jacobi, it
uses the _already-updated_ values of `x_1 .. x_{i-1}` from the current
sweep instead of only the previous sweep's values. This makes each
iteration depend on the update order but converges faster in practice
whenever it converges at all (guaranteed for diagonally dominant or
symmetric positive-definite `A`).

`A` here is banded: only `k` diagonals (`k` odd) are non-zero, all others
are zero. Instead of allocating a full `n x n` matrix, the program stores
just those `k` diagonals plus the independent-term vector `b`, and the
per-row sum `sum_{j != i} A[i][j] * x_j` is computed by walking only the
diagonals that actually intersect row `i` (split into the diagonals to the
left of the main one and the diagonals to the right, `somaEsquerda` /
`somaDireita`).

## How it works

1. `inputs()` reads the system dimension `n`, the diagonal count `k`, and
   `k + 1` expressions (one per diagonal, plus the independent-term
   vector), each evaluated at `x = 0, 1, ..., n-1` to materialize its
   values.
2. `criaSL()` builds the diagonal storage from those expressions.
3. `calculaGauss()` runs the Gauss-Seidel sweeps until a stopping
   criterion is met, timing the computation with `timestamp()`.

### Stopping criteria

The loop stops once **both** hold:

1. `MAXIT` — maximum number of iterations, from input.
2. `maiorER < epsilon` — the largest relative error, across all `x_i`,
   between the current and previous sweep's value, must drop below the
   input tolerance `epsilon`.

Because both conditions must hold simultaneously (implemented as a
`do...while`), the loop generally only stops once `maiorER < epsilon` is
satisfied, or `MAXIT` is reached first.

## Building and running

```sh
make
./ep02 < entrada.in > saida.out
```

Requires `libmatheval` (`-lmatheval`, declared in the `makefile`).

### Input format (`entrada.in`)

```
n k                  # system dimension, number of diagonals (odd)
diag_1(j)            # expression for each diagonal, evaluated at j = 0..n-1
...
diag_k(j)
b(j)                 # independent-term vector, expression evaluated at j = 0..n-1
epsilon maxit        # tolerance, maximum iterations
```
