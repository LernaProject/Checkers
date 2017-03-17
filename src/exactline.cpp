#include "testlib.h"
#include <sstream>
#include <string>

bool tryReadTokenTo(std::string& s, InStream& stream) {
    if (stream.seekEoln())
        return false;
    stream.readTokenTo(s);
    return true;
}

int main(int argc, char* argv[ ]) {
    setName("compare lines as sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = 1, m = 0, lastLine = 0;
    std::string j, p;
    std::ostringstream repr;

    while (!ans.eof()) {
        bool jnl = !tryReadTokenTo(j, ans);
        bool pnl = !tryReadTokenTo(p, ouf);
        m++;
        if (jnl && pnl) {
            n++;
            m = 0;
        } else if (jnl && !pnl)
            quitf(
                _wa, "Extra %d%s token in %d%s line: '%s'",
                m, englishEnding(m).c_str(), n, englishEnding(n).c_str(), compress(p).c_str()
            );
        else if (pnl && !jnl)
            quitf(
                _wa, "Missing %d%s token in %d%s line: '%s' expected",
                m, englishEnding(m).c_str(), n, englishEnding(n).c_str(), compress(j).c_str()
            );
        else {
            lastLine = n;
            if (j != p)
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
    if (!ouf.seekEof()) {
        ouf.readTokenTo(p);
        quitf(_wa, "Extra tokens in participant's output: '%s'", compress(p).c_str());
    }

    if (lastLine == 1)
        quitf(_ok, "'%s'", compress(repr.str()).c_str());
    else
        quitf(_ok, "%d lines", lastLine);
}
