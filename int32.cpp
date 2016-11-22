#include "testlib.h"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[ ]) {
    setName("compare ordered sequences of signed int32 numbers");
    registerTestlibCmd(argc, argv);

    int n = 0;
    int j, p = 0;
    ostringstream firstElems;

    while (!ans.seekEof() && !ouf.seekEof()) {
        n++;
        j = ans.readInt();
        p = ouf.readInt();
        if (j != p) {
            string ending = englishEnding(n);
            quitf(_wa, "%d%s numbers differ: expected '%d', found '%d'",
                n, ending.c_str(), j, p
            );
        } else if (n <= 5) {
            if (n > 1)
                firstElems << ' ';
            firstElems << j;
        }
    }

    int extraInAnsCount = 0;
    while (!ans.seekEof()) {
        ans.readInt();
        extraInAnsCount++;
    }

    int extraInOufCount = 0;
    while (!ouf.seekEof()) {
        ouf.readInt();
        extraInOufCount++;
    }

    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements",
            n + extraInAnsCount, n
        );

    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements",
            n + extraInOufCount, n
        );

    if (n == 1)
        quitf(_ok, "'%d'", p);
    else if (n <= 5) {
        string s = compress(firstElems.str());
        quitf(_ok, "%d numbers: '%s'", n, s.c_str());
    } else
        quitf(_ok, "%d numbers", n);
}
