#include "testlib.h"
#include <sstream>

int main(int argc, char* argv[ ]) {
    setName("compare sequences of signed int32 numbers");
    registerTestlibCmd(argc, argv);

    int n = 0;
    int j, p = 0;
    std::ostringstream repr;

    while (!ans.seekEof()) {
        n++;
        j = ans.readInt();
        p = ouf.readInt();

        if (j != p)
            expectedButFound(_wa, j, p, "%d%s numbers differ", n, englishEnding(n).c_str());

        if (n <= 5) {
            if (n > 1)
                repr << ' ';
            repr << p;
        }
    }

    if (n == 1)
        quitf(_ok, "%d", p);
    else if (n <= 5)
        quitf(_ok, "%d numbers: '%s'", n, compress(repr.str()).c_str());
    else
        quitf(_ok, "%d numbers", n);
}
