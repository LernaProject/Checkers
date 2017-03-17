#include "testlib.h"
#include <sstream>
#include <string>

void readBigIntTo(std::string& s, InStream& stream) {
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
    setName(
        "compare sequences of arbitrary-length signed integers, "
        "returning PE if their lengths differ"
    );
    registerTestlibCmd(argc, argv);

    int n = 0;
    std::string j, p;
    std::ostringstream repr;

    while (!ans.seekEof()) {
        n++;
        readBigIntTo(j, ans);
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

    if (n == 1)
        quit(_ok, compress(p).c_str());
    else if (n <= 5)
        quitf(_ok, "%d numbers: '%s'", n, compress(repr.str()).c_str());
    else
        quitf(_ok, "%d numbers", n);
}
