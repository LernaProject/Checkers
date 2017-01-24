#include "testlib.h"

#ifndef PREC
#   error Define PREC to required precision.
#endif

#define DO_STR(x) #x
#define STR(x) DO_STR(x)
#define DO_EXP(x) 1e-##x
#define EXP(x) DO_EXP(x)

#define SPEC "%." STR(PREC) "f"
#define EPS EXP(PREC)

int main(int argc, char* argv[ ]) {
    setName("compare two sequences of doubles, max absolute or relative error = 1e-" STR(PREC));
    registerTestlibCmd(argc, argv);

    int n = 0;
    double j = 0, p = 0;

    while (!ans.seekEof()) {
        n++;
        j = ans.readDouble();
        p = ouf.readDouble();
        if (!doubleCompare(j, p, EPS))
            quitf(
                _wa, "%d%s numbers differ: expected '" SPEC "', found '%.10f', error '%.10f'",
                n, englishEnding(n).c_str(), j, p, doubleDelta(j, p)
            );
    }

    if (n == 1)
        quitf(_ok, "expected '" SPEC "', found '%.10f', error '%.10f'", j, p, doubleDelta(j, p));
    else
        quitf(_ok, "%d numbers", n);
}
