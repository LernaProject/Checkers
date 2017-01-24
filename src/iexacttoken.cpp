#include "testlib.h"
#include <sstream>
#include <string>

using namespace std;

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
    setName("compare sequences of tokens (case-insensitive)");
    registerTestlibCmd(argc, argv);

    int n = 0;
    string j, p;
    ostringstream repr;

    while (!ans.seekEof()) {
        n++;
        ans.readTokenTo(j);
        quitif(ouf.seekEof(),
            _wa, "Unexpected EOF in participant's output: '%s' expected", compress(j).c_str()
        );
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
