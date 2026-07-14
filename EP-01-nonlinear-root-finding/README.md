# Nonlinear Root Finding — Newton-Raphson & Secant

Finds the root of a single nonlinear equation `f(x) = 0`, computing both
the Newton-Raphson and the Secant approximations side by side at every
iteration so their convergence can be compared.

## Theory

**Newton-Raphson** builds the tangent line to `f` at the current estimate
`x_n` and uses the point where that tangent crosses zero as the next
estimate:

```
x_{n+1} = x_n - f(x_n) / f'(x_n)
```

This is the fixed-point iteration `x_{n+1} = phi(x_n)` with
`phi(x) = x - f(x)/f'(x)`. It converges quadratically near a simple root,
but requires the derivative `f'`, which this program obtains by symbolic
differentiation of the user-supplied expression (via libmatheval) rather
than a numeric approximation.

**Secant method** replaces the derivative with a finite-difference slope
between the two most recent iterates, `x_n` and `x_{n-1}`:

```
x_{n+1} = x_n - f(x_n) * (x_n - x_{n-1}) / (f(x_n) - f(x_{n-1}))
```

It converges slightly slower than Newton-Raphson (superlinear, order
≈1.618) but doesn't need `f'` — useful when the derivative is hard to
obtain. Because it needs two previous points, the algorithm here only
starts comparing the two methods from the third iteration onward.

## How it works

`main.c` calls `init()` in `functions.c`, which:

1. Reads `f(x)` as a string from `stdin`, plus the initial guess `x0`,
   tolerance `epsilon`, and maximum iteration count `max_iter`.
2. Builds `f`, its derivative `f'`, `phi(x) = x - f(x)/f'(x)`, and the
   secant update formula, all as libmatheval expression trees.
3. Iterates both methods in lockstep, printing one CSV row per iteration
   with both current values, their respective convergence criteria, the
   absolute/relative error between the two methods' results, and the ULP
   (unit-in-the-last-place) distance between them.

### Stopping criteria

The loop keeps going while **all** of the following hold; it stops as soon
as any one fails:

1. `iter <= max_iter` — hard cap on iteration count (must be ≥ 3, since
   the secant method needs two prior points before it can start).
2. `newton_crit >= epsilon` — relative error between the last two
   Newton-Raphson iterates.
3. `secante_crit >= epsilon` — relative error between the last two Secant
   iterates.
4. `ulp > 1` — the two methods' current results still differ by more than
   1 unit in the last place (i.e. they haven't yet converged to the same
   representable double).

## Building and running

```sh
make
./ep01.out < entrada.in > saida.csv
```

Requires `libmatheval` (`-lmatheval`, declared in the `makefile`).

### Input format (`entrada.in`)

```
f(x)              # e.g. "2^x"
x0                # initial guess
epsilon           # tolerance
max_iter          # maximum number of iterations
```

### Output

CSV to stdout (or the redirected file), one row per iteration:

```
iter, newton_x, newton_crit, secant_x, secant_crit, abs_error(nwt,sec), rel_error(nwt,sec), ulp
```
