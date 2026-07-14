# Numerical Integration — Monte Carlo vs. Rectangle Rule

Numerically integrates the Styblinski-Tang function over `[a, b]` in 2, 4
and 8 dimensions using Monte Carlo integration, and compares it against
the Rectangle rule (computed for the 2-dimensional case) — both as a
correctness check and a performance benchmark.

## Theory

The [Styblinski-Tang function](https://www.sfu.ca/~ssurjano/stybtang.html)
in `n` dimensions is:

```
f(x_1, ..., x_n) = (1/2) * sum_i (x_i^4 - 16*x_i^2 + 5*x_i)
```

**Rectangle rule:** approximates the integral over `[a, b]` by summing
`f` at `npontos` evenly-spaced sample points, each weighted by the cell
width `h = (b - a) / npontos`:

```
integral ≈ h * sum_j f(x_j)   (per dimension, extended to n dimensions)
```

**Monte Carlo integration:** instead of a regular grid, averages `f` over
`namostras` uniformly _random_ points in `[a, b]^n`, scaled by the volume
`(b - a)^n`:

```
integral ≈ (b - a)^n * (1/namostras) * sum_i f(sample_i)
```

Monte Carlo's error shrinks as `O(1/sqrt(namostras))` regardless of
dimension, which is why it's the practical choice in high dimensions where
a regular grid would need exponentially many points; the Rectangle rule
converges faster in low dimensions but degrades quickly as `n` grows.

### Algebraic simplification actually implemented

Because the Styblinski-Tang sum is over `n` structurally-identical terms
sampled independently and identically, the code doesn't literally loop
over each of the `n` variables per sample point. It draws one random value
per sample, evaluates the single-variable expression `x^4 - 16x^2 + 5x`,
and relies on the fact that the sum over `n` i.i.d. dimensions collapses
into `n` times a single term's expectation. Combined with the leading
`1/2`, this leaves a constant factor `n/2` (0 for `n=2`, 2 for `n=4`, 4 for
`n=8`) that multiplies a _single_ accumulated sum — eliminating the inner
per-dimension loop entirely. See `LEIAME.md`-derived notes below for the
full derivation; the resulting formulas are:

- Monte Carlo: `(b-a)^n * (1/namostras^n) * (n/2) * sum(f(x))`
- Rectangles: `h^2 * npontos * (n/2) * sum(f(x))`

This is a performance optimization specific to this function's structure,
not a generally-applicable shortcut.

## How it works

`main.c` calls, in order:

1. `styblinskiTang(a, b, POINTS_NUMBER)` — runs Monte Carlo integration
   for 2, 4 and 8 dimensions (`POINTS_NUMBER = 10,000,000` samples each),
   printing the elapsed time for each.
2. `retangulos_xy(a, b, POINTS_NUMBER)` — runs the Rectangle rule for the
   2-dimensional case with the same point count.

Both report their timing (via `utils.c`'s `timestamp()`) and are written
to minimize redundant work inside the hot loop: no unnecessary library
calls (`math.h`), a single contiguous heap allocation, no data dependencies
between loop iterations, and loop-invariant values hoisted out.

## Building and running

```sh
make
./labMonteCarlo <a> <b>
```

Example: `./labMonteCarlo -5 5` integrates over `[-5, 5]` in each
dimension.

No external dependencies beyond the standard C library and `libm`.
