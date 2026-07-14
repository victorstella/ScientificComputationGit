# Nonlinear Systems — Newton's Method

Solves systems of nonlinear equations with Newton's method, using
Gaussian elimination with partial pivoting to solve the linear system at
each iteration. Source lives in [`src/`](src/).

## Theory

Newton's method for a single equation (see
[EP-01](../EP-01-nonlinear-root-finding/)) generalizes to a system of `n`
nonlinear equations in `n` unknowns,
`F(x) = (f_1(x_1,...,x_n), ..., f_n(x_1,...,x_n)) = 0`. At each iterate
`x^(k)`, the multivariate analogue of `f'(x)` is the **Jacobian matrix**
`J`, whose entry `J[i][j] = ∂f_i/∂x_j` is evaluated at `x^(k)`. Instead of
dividing by a scalar derivative as in the 1-D case, the update step
`delta` solves the _linear_ system:

```
J(x^(k)) * delta = -F(x^(k))
x^(k+1) = x^(k) + delta
```

This program builds `J` symbolically (partial-differentiating each
equation's string expression with respect to each variable, via
libmatheval) and then solves the resulting linear system for `delta` at
every iteration using **Gaussian elimination with partial pivoting**:
`triangulariza()` reduces the system to upper-triangular form, swapping
rows at each step to bring the largest-magnitude candidate onto the
pivot position (improving numerical stability), and `retroSubst()`
back-substitutes to recover `delta`.

## How it works

The program processes one or more nonlinear systems from the same input
stream, looping until input is exhausted:

1. `inputs()` reads `n` equations (as strings), `n` initial guesses, the
   tolerance `epsilon`, and `MAXIT`.
2. `newton()` repeats, each iteration:
   - Evaluates all `n` equations at the current guess
     (`maiorFunc()` also returns the largest `|f_i(x)|`, used below).
   - Builds the Jacobian (`criaJacobs()`) and evaluates it at the current
     guess (`calculaSL()`).
   - Solves `J * delta = -F(x)` via Gaussian elimination
     (`calculaGauss()`, in `gauss.c`).
   - Updates `x^(k+1) = x^(k) + delta` (`calculaNovoX()`).
3. Prints the trajectory of `x` at every iteration, plus per-phase timing
   (Jacobian construction, Jacobian evaluation, linear solve).

### Stopping criteria

The loop stops once **all** of the following hold:

1. `iter > MAXIT` — iteration cap reached, from input.
2. `maiorFunc() < epsilon` — every equation is within tolerance of zero
   at the current `x`.
3. `|delta_i| <= epsilon` for every `i` — the update step itself has
   become negligible.

## Building and running

```sh
cd src
make
./newtonSNL < entrada.in > saida.out
```

`./newtonSNL` with no redirection also works, reading from stdin and
writing to stdout interactively.

Requires `libmatheval` (`-lmatheval`, declared in the `makefile`).

### Input format

```
n                    # number of equations / unknowns
f_1(x1,...,xn)       # one equation per line, using x1, x2, x3 as variable names
...
f_n(x1,...,xn)
x1_0 x2_0 ... xn_0   # initial guess
epsilon maxit        # tolerance, maximum iterations
```

Repeat the block to solve multiple systems in one run; the program stops
when it can no longer read a system size.

## Relationship to T-2

[T-2](../T-2-broyden-tridiagonal-newton/) solves the same class of
problem (nonlinear systems via Newton's method) but specialized to the
Broyden tridiagonal system, whose Jacobian is tridiagonal by
construction — replacing this project's dense Gaussian elimination with a
structure that stores only the three relevant diagonals, and profiling
the result with LIKWID.
