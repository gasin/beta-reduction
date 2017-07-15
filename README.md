# beta-reduction
inplement beta-reduction with C++

## Description
Leftmost strategy and de-bruijn index are used.

## Compile
``` shell
$ gmake
```

## Usage
The syntax is similar to OCaml.
Just show some input examples below.

``` shell
$ (\f f y x) (\x \y x)
```

``` shell
$ (\f \x f (f x)) (\x x)
```
