# Broyden Tridiagonal System — Newton's Method

A specialized, LIKWID-profiled variant of [T-1](../T-1-newton-nonlinear-systems/):
solves the classic **Broyden tridiagonal** nonlinear system with Newton's
method, exploiting the fact that its Jacobian is tridiagonal to avoid
dense Gaussian elimination. Source lives in [`src/`](src/).

## Theory

The **Broyden tridiagonal function** is a standard nonlinear-solver test
problem. For `i = 1..n` (with `x_0 = x_{n+1} = 0`):

```
f_i(x) = (3 - 2*x_i)*x_i - x_{i-1} - 2*x_{i+1} + 1
```

(boundary equations drop the missing neighbor term). `broyden.sh`
generates exactly this system for a range of sizes `n`
(3, 10, 32, ... 4096), each equation referencing only its own variable and
its immediate left/right neighbors — which is what makes the Jacobian
`J[i][j] = ∂f_i/∂x_j` tridiagonal: `J[i][j] = 0` whenever `|i - j| > 1`.

As in T-1, Newton's method solves `J(x^(k)) * delta = -F(x^(k))` and
updates `x^(k+1) = x^(k) + delta` at every iteration. T-1's implementation
represents `J` as a dense `n x n` matrix and solves for `delta` via
Gaussian elimination, `O(n^3)` per iteration. Here, `sl_t` (`sl_t.c`/`.h`)
instead stores only the three diagonals that can be non-zero — principal
(`jacobi_solution_principal`), and the (here constant, since the
off-diagonal terms `-1` and `-2` don't depend on `x`) super/sub-diagonal
values `jacobi_solution_superior` / `jacobi_solution_inferior` — turning
Jacobian storage and evaluation from `O(n^2)` into `O(n)`.

`gauss.c`'s `retroSubst()` solves the resulting tridiagonal system for
`delta` with a fixed number of relaxation sweeps (4), each pass updating
`delta_x[i]` from the current `evaluated_curr_x[i]` and its neighbors'
`delta_x` values — a Gauss-Seidel-style sweep over the tridiagonal system
rather than a direct (e.g. Thomas algorithm) solve.

## How it works

1. `inputs()` reads `n` equations, `n` initial guesses, `epsilon`, and
   `MAXIT`, and builds an `sl_t` via `inicia_sl_t()`.
2. `inicia_sl_t()` calls `monta_jacobi()`, which differentiates
   `f_1` symbolically once (with respect to `x1` and `x2`) and `f_2` once
   (with respect to `x3`) to obtain the principal/super/sub-diagonal
   _expressions_ — reused for every row, since all interior equations
   share the same structure.
3. `newton()` loops: evaluates all `f_i` at the current `x`
   (`calcula_funcs`), checks whether the largest `|f_i(x)|` is already
   below `epsilon`, evaluates the principal diagonal at each `x_i`
   (`calcula_jacobi`), and updates `x` from `delta_x`
   (`calcula_novo_x`).
4. `main.c` wraps the whole run in `LIKWID_MARKER_INIT`/`_CLOSE`, and
   `verifica_opt.sh` (mirroring EP-03's `confere_opt.sh`) is meant to
   sweep over system sizes and collect runtime/L2/L3/FLOPS counters into
   `dados.csv` for the same kind of performance analysis as EP-03.

### Status

This is a work-in-progress performance-lab branch of T-1, not a
finished/verified solver: `newton()`'s main loop does not currently call
`calcula_gauss()` (in `gauss.c`) to solve for `delta_x`, so `delta_x`
never actually gets updated from the tridiagonal Jacobian — wiring that
call in is the missing step to make the solver converge like T-1 does.
`verifica_opt.sh` also references a couple of variables
(`$exeGeraSL`, `$slFile`) that aren't defined in that script. Treat this
folder as the tridiagonal-Jacobian/LIKWID scaffolding for T-1's method
rather than a drop-in replacement.

## Building and running

```sh
cd src
make
./newtonSNL < broyden.dat   # or pipe output of ./broyden.sh
```

Requires `libmatheval` (`-lmatheval`) and, for the LIKWID markers compiled
into `main.c`, [LIKWID](https://github.com/RRZE-HPC/likwid)
(`likwid.h` / `liblikwid`) — the `makefile` here does not currently declare
the LIKWID include/link flags, so add them manually
(`-I<likwid>/include -DLIKWID_PERFMON -L<likwid>/lib -llikwid`) if you hit
a missing-header error, matching the pattern in
[EP-03's Makefile](../EP-03-gauss-jacobi-performance/Makefile).

### Input format

Same as [T-1](../T-1-newton-nonlinear-systems/#input-format); `broyden.sh`
generates it directly:

```sh
./broyden.sh > broyden.dat
```
