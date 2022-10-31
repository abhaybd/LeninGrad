# LeninGrad

![CI Status](https://github.com/abhaybd/LeninGrad/actions/workflows/ccpp.yml/badge.svg)

LeninGrad is the people's auto-differentiation library, providing easy  autodifferentiation for first and higher-order derivatives!
Essentially, LeninGrad provides drop-in types `dfloat` and `ddouble` which automatically allow for analytical differentiation.

## Code snippets:

For example, if your code is:
```c++
double a = ..., b = ...;
double c = std::cos(a) * std::sin(b);
```

Getting the derivative of `c` wrt `a` and `b` is as easy as changing the above to:
```c++
using leningrad::ddouble;

ddouble a = ..., b = ...;
ddouble c = leningrad::cos(a) * leningrad::sin(b);

auto dc = differentiate(c);
ddouble dcda = dc.wrt(a);
ddouble dcdb = dc.wrt(b);
```

You can also calculate higher order derivatives!
```c++
// d^2c/da^2
ddouble d2cda2 = differentiate(c, a, 2);
```

Cross derivatives are easy too:
```c++
// d^2c/dadb
ddouble d2cdadb = differentiate(c, {a, b});
```

Derivatives are themselves differentiable too:
```c++
ddouble dcda = differentiate(c).wrt(a);
ddouble foo = 2 * leningrad::exp(dcda);
ddouble bar = differentiate(foo).wrt(dcda);
```
