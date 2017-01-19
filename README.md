# Lerna.Checkers

To compile checkers, run `make -j4`. You'll be given tons of warnings, unless they are fixed in
`testlib`. Build should succeed though.


## Available checkers

* `ok` — A stub checker that always returns `OK`.
* `fail` — A stub checker that always returns `FAIL`.
* `char`, `ichar` — Compares files character by character. Extremely strict, and therefore should
  rarely be used.
* `token`, `itoken` — Compares files token by token, ignoring whitespace and line breaks.
* `line`, `iline` — Compares files token by token, ignoring whitespace but **not** line breaks.
* `yesno` — Compares two sequences of `YES` and `NO`, case-insensitive.
* `int` — Compares two sequences of arbitrary-length signed integral numbers.
* `float1` – `float10` — Compares two sequences of real numbers. Absolute or relative error between
  corresponding elements must not exceed 10<sup>-N</sup>.

Checkers prefixed with an `i` are case-insensitive.
