#include "testlib.h"
#include <sstream>
#include <string>

bool tryReadBigIntTo(std::string& s, InStream& stream) {
    if (stream.seekEoln())
        return false;
    stream.readTokenTo(s);
    size_t i = s.front() == '-';
    if (i == s.length())
        stream.quit(_pe, "An integer expected, but '-' found");
    if (s[i] == '0' && s.length() > 1)
        stream.quitf(_pe, "Leading zeroes are not allowed: '%s'", compress(s).c_str());
    for (; i != s.length(); i++)
        if (s[i] < '0' || s[i] > '9')
            stream.quitf(_pe, "An integer expected, but '%s' found", compress(s).c_str());
    return true;
}

int main(int argc, char* argv[ ]) {
    setName(
        "compare lines as sequences of arbitrary-length signed integers, "
        "returning PE if their lengths differ"
    );
    registerTestlibCmd(argc, argv);

    int n = 1, m = 0, total = 0;
    std::string j, p;
    std::ostringstream repr;

    while (!ans.eof()) {
        bool jnl = !tryReadBigIntTo(j, ans);
        bool pnl = !tryReadBigIntTo(p, ouf);
        m++;
        if (jnl && pnl) {
            n++;
            m = 0;
        } else if (jnl && !pnl)
            quitf(
                _pe, "Extra %d%s number in %d%s line: '%s'",
                m, englishEnding(m).c_str(), n, englishEnding(n).c_str(), compress(p).c_str()
            );
        else if (pnl && !jnl)
            quitf(
                _pe, "Missing %d%s number in %d%s line: '%s' expected",
                m, englishEnding(m).c_str(), n, englishEnding(n).c_str(), compress(j).c_str()
            );
        else {
            if (j != p)
                expectedButFound(
                    _wa, compress(j).c_str(), compress(p).c_str(),
                    "%d%s numbers in %d%s lines differ",
                    m, englishEnding(m).c_str(), n, englishEnding(n).c_str()
                );

            total++;
            if (repr.tellp() <= 64) {
                if (total > 1)
                    repr << ' ';
                repr << p;
            }
        }
    }

    if (total == 1)
        quit(_ok, compress(p).c_str());
    else if (total <= 5)
        quitf(_ok, "%d numbers: '%s'", total, compress(repr.str()).c_str());
    else
        quitf(_ok, "%d numbers", total);
}
