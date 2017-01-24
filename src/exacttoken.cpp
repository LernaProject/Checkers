#include "testlib.h"
#include <sstream>
#include <string>

int main(int argc, char* argv[ ]) {
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = 0;
    std::string j, p;
    std::ostringstream repr;

    while (!ans.seekEof()) {
        n++;
        ans.readTokenTo(j);
        quitif(ouf.seekEof(),
            _wa, "Unexpected EOF in participant's output: '%s' expected", compress(j).c_str()
        );
        ouf.readTokenTo(p);

        if (j != p)
            expectedButFound(
                _wa, compress(j).c_str(), compress(p).c_str(),
                "%d%s tokens differ", n, englishEnding(n).c_str()
            );

        if (repr.tellp() < 63) {
            if (n > 1)
                repr << ' ';
            repr << p;
        }
    }
    if (!ouf.seekEof()) {
        ouf.readTokenTo(p);
        quitf(_wa, "Extra tokens in participant's output: '%s'", compress(p).c_str());
    }

    if (n == 1)
        quit(_ok, compress(p).c_str());
    else if (n <= 5)
        quitf(_ok, "%d tokens: '%s'", n, compress(repr.str()).c_str());
    else
        quitf(_ok, "%d tokens", n);
}
