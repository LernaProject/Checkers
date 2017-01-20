#include "testlib.h"
#include <sstream>
#include <string>

using namespace std;

bool tryReadTokenTo(string& s, InStream& stream) {
    if (stream.seekEoln())
        return false;
    stream.readTokenTo(s);
    return true;
}

char toLower(char c) {
    return c >= 'A' && c <= 'Z' ? char(c | 0x20) : c;
}

bool icompare(const string& a, const string& b) {
    if (a.length() != b.length())
        return false;
    for (size_t i = 0; i < a.length(); i++)
        if (toLower(a[i]) != toLower(b[i]))
            return false;
    return true;
}

int main(int argc, char* argv[ ]) {
    setName(
        "compare lines as sequences of tokens (case-insensitive), "
        "returning PE if their lengths differ"
    );
    registerTestlibCmd(argc, argv);

    int n = 1, m = 0, lastLine = 0;
    string j, p;
    ostringstream repr;

    while (!ans.eof()) {
        bool jnl = !tryReadTokenTo(j, ans);
        bool pnl = !tryReadTokenTo(p, ouf);
        m++;
        if (jnl && pnl) {
            n++;
            m = 0;
        } else if (jnl && !pnl)
            quitf(
                _pe, "Extra %d%s token in %d%s line: '%s'",
                m, englishEnding(m).c_str(), n, englishEnding(n).c_str(), compress(p).c_str()
            );
        else if (pnl && !jnl)
            quitf(
                _pe, "Missing %d%s token in %d%s line: '%s' expected",
                m, englishEnding(m).c_str(), n, englishEnding(n).c_str(), compress(j).c_str()
            );
        else {
            lastLine = n;
            if (!icompare(j, p))
                expectedButFound(
                    _wa, compress(j).c_str(), compress(p).c_str(),
                    "%d%s tokens in %d%s lines differ",
                    m, englishEnding(m).c_str(), n, englishEnding(n).c_str()
                );

            if (n == 1 && repr.tellp() <= 64) {
                if (m > 1)
                    repr << ' ';
                repr << p;
            }
        }
    }

    if (lastLine == 1)
        quitf(_ok, "'%s'", compress(repr.str()).c_str());
    else
        quitf(_ok, "%d lines", lastLine);
}
