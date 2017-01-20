#include "testlib.h"
#include <sstream>
#include <string>

using namespace std;

void readBigIntTo(string& s, InStream& stream) {
    stream.readTokenTo(s);
    size_t i = s.front() == '-';
    if (i == s.length())
        stream.quit(_pe, "An integer expected, but '-' found");
    if (s[i] == '0' && s.length() > 1)
        stream.quitf(_pe, "Leading zeroes are not allowed: '%s'", compress(s).c_str());
    for (; i != s.length(); i++)
        if (s[i] < '0' || s[i] > '9')
            stream.quitf(_pe, "An integer expected, but '%s' found", compress(s).c_str());
}

int main(int argc, char* argv[ ]) {
    setName("compare sequences of arbitrary-length signed integers");
    registerTestlibCmd(argc, argv);

    int n = 0;
    string j, p;
    ostringstream repr;

    while (!ans.seekEof()) {
        n++;
        readBigIntTo(j, ans);
        quitif(ouf.seekEof(),
            _wa, "Unexpected EOF in participant's output: '%s' expected", compress(j).c_str()
        );
        readBigIntTo(p, ouf);

        if (j != p)
            expectedButFound(
                _wa, compress(j).c_str(), compress(p).c_str(),
                "%d%s numbers differ", n, englishEnding(n).c_str()
            );

        if (repr.tellp() < 63) {
            if (n > 1)
                repr << ' ';
            repr << p;
        }
    }
    if (!ouf.seekEof()) {
        readBigIntTo(p, ouf);
        quitf(_wa, "Extra numbers in participant's output: '%s'", compress(p).c_str());
    }

    if (n == 1)
        quit(_ok, compress(p).c_str());
    else if (n <= 5)
        quitf(_ok, "%d numbers: '%s'", n, compress(repr.str()).c_str());
    else
        quitf(_ok, "%d numbers", n);
}
