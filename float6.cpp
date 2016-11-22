#include "testlib.h"

const double EPS = 1e-6;

int main(int argc, char* argv[ ]) {
    setName("compare two sequences of doubles, max absolute or relative error = %.6f", EPS);
    registerTestlibCmd(argc, argv);
    int n = 0;
    double j = 0, p = 0;
    while (!ans.seekEof()) {
        n++;
        j = ans.readDouble();
        p = ouf.readDouble();
        if (!doubleCompare(j, p, EPS))
            quitf(_wa, "%d%s numbers differ: expected '%.6f', found '%.6f', error '%.6f'",
                n, englishEnding(n).c_str(), j, p, doubleDelta(j, p)
            );
    }
    if (n == 1)
        quitf(_ok, "found '%.6f', expected '%.6f', error '%.6f'", p, j, doubleDelta(j, p));
    quitf(_ok, "%d numbers", n);
}
