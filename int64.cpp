#include "testlib.h"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[ ]) {
    setName("compare ordered sequences of signed int64 numbers");
    registerTestlibCmd(argc, argv);

    int n = 0;
    long long j, p = 0;
    ostringstream firstElems;

    while (!ans.seekEof() && !ouf.seekEof()) {
        n++;
        j = ans.readLong();
        p = ouf.readLong();
        if (j != p) {
            string ending = englishEnding(n);
            quitf(_wa, "%d%s numbers differ: expected \"" I64 "\", found \"" I64 "\"",
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
        ans.readLong();
        extraInAnsCount++;
    }
    
    int extraInOufCount = 0;
    while (!ouf.seekEof()) {
        ouf.readLong();
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
        quitf(_ok, "\"" I64 "\"", p);
    else if (n <= 5) {
        string s = compress(firstElems.str());
        quitf(_ok, "%d numbers: \"%s\"", n, s.c_str());
    } else
        quitf(_ok, "%d numbers", n);
}
