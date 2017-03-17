#include "testlib.h"
#include <sstream>
#include <string>

char toLower(char c) {
    return c >= 'A' && c <= 'Z' ? char(c | 0x20) : c;
}

bool icompare(const std::string& a, const std::string& b) {
    if (a.length() != b.length())
        return false;
    for (size_t i = 0; i < a.length(); i++)
        if (toLower(a[i]) != toLower(b[i]))
            return false;
    return true;
}

int main(int argc, char* argv[ ]) {
    setName("compare sequences of tokens (case-insensitive), returning PE if their lengths differ");
    registerTestlibCmd(argc, argv);

    int n = 0;
    std::string j, p;
    std::ostringstream repr;

    while (!ans.seekEof()) {
        n++;
        ans.readTokenTo(j);
        ouf.readTokenTo(p);

        if (!icompare(j, p))
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

    if (n == 1)
        quit(_ok, compress(p).c_str());
    else if (n <= 5)
        quitf(_ok, "%d tokens: '%s'", n, compress(repr.str()).c_str());
    else
        quitf(_ok, "%d tokens", n);
}
