# Scientific Computation

Coursework from a Scientific Computation class (UFPR), implemented in C. Each
subfolder is a self-contained assignment: a numerical method applied to a
concrete problem, plus (for the later assignments) a performance-analysis
component comparing naive and optimized implementations.

All programs share the same shape: read a problem definition from `stdin`
(or a file), iterate a numerical method until a stopping criterion is met,
and print the result. Function expressions (e.g. `3*x+1`, `2^x`) are parsed
and evaluated at runtime using [GNU libmatheval](https://www.gnu.org/software/libmatheval/),
which is why every project that reads user-supplied equations links against
`-lmatheval`.

## Assignments

| Folder                                                                  | Method                                            | Problem                                                                             |
| ----------------------------------------------------------------------- | ------------------------------------------------- | ----------------------------------------------------------------------------------- |
| [EP-01-nonlinear-root-finding](EP-01-nonlinear-root-finding/)           | Newton-Raphson & Secant                           | Find the root of a single nonlinear equation `f(x) = 0`                             |
| [EP-02-gauss-seidel-linear-systems](EP-02-gauss-seidel-linear-systems/) | Gauss-Seidel                                      | Solve a banded linear system `Ax = b` iteratively                                   |
| [EP-03-gauss-jacobi-performance](EP-03-gauss-jacobi-performance/)       | Gauss-Jacobi                                      | Solve `Ax = b`; naive vs. cache/SIMD-optimized implementation, profiled with LIKWID |
| [EP-04-monte-carlo-integration](EP-04-monte-carlo-integration/)         | Monte Carlo & Rectangle rule                      | Numerically integrate the Styblinski-Tang function in 2, 4 and 8 dimensions         |
| [T-1-newton-nonlinear-systems](T-1-newton-nonlinear-systems/)           | Newton's method + Gaussian elimination            | Solve systems of nonlinear equations                                                |
| [T-2-broyden-tridiagonal-newton](T-2-broyden-tridiagonal-newton/)       | Newton's method, exploiting tridiagonal structure | Solve the Broyden tridiagonal system; optimized/benchmarked version of T-1          |

`EP` stands for _Exercício Programa_ (programming assignment) and `T` for
_Trabalho_ (take-home assignment) — the course's original naming scheme,
kept here for traceability, with a descriptive suffix added for clarity.

## Building

Every subfolder has its own `Makefile`/`makefile` and builds independently:

```sh
cd EP-01-nonlinear-root-finding
make
```

Requirements, by project:

- **All EP/T folders that parse user equations** (everything except EP-03
  and EP-04): [GNU libmatheval](https://www.gnu.org/software/libmatheval/)
  (`libmatheval-dev` or equivalent) — provides runtime parsing/evaluation/
  differentiation of math expressions typed as strings.
- **EP-03** and **T-2**: [LIKWID](https://github.com/RRZE-HPC/likwid) for
  hardware performance counters (cache traffic, FLOPS). EP-03's `Makefile`
  points at a hardcoded LIKWID install path (`/home/soft/likwid`) — adjust
  it to your own install.
- A C compiler (`gcc`) and `make`.

See each subfolder's README for exact build/run instructions and input
format.

## Theory in brief

- **Root finding (EP-01):** Newton-Raphson uses the function's derivative
  to build a linear approximation and jump to where it crosses zero;
  the Secant method approximates that derivative with a finite difference
  between the two latest iterates, avoiding symbolic differentiation.
- **Linear systems (EP-02, EP-03):** Gauss-Seidel and Gauss-Jacobi are
  iterative methods for `Ax = b` that repeatedly refine an approximation of
  `x`, isolating each `x_i` from its equation and plugging in the current
  estimates of the others. Gauss-Seidel uses freshly updated values within
  the same sweep (faster convergence, sequential); Gauss-Jacobi uses only
  values from the previous sweep (slower convergence, but each entry is
  independent — parallelizable and cache-friendly, which is what EP-03's
  optimized version exploits).
- **Numerical integration (EP-04):** the Rectangle rule sums the function
  value over a regular grid of sample points; Monte Carlo integration
  instead averages the function over uniformly _random_ sample points. Both
  estimate the same integral, but converge differently, and accumulate
  floating-point error differently as the sample count grows.
- **Nonlinear systems (T-1, T-2):** Newton's method for systems generalizes
  Newton-Raphson: at each iterate, the Jacobian matrix of partial
  derivatives is evaluated and a _linear_ system is solved for the update
  step `delta` (via Gaussian elimination with partial pivoting). T-2 solves
  the same kind of problem for the Broyden tridiagonal system, whose
  Jacobian is tridiagonal by construction — so the dense Gaussian
  elimination from T-1 is replaced with a specialized structure that only
  stores the three relevant diagonals, and the whole pipeline is profiled
  with LIKWID.
