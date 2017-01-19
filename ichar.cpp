#include "testlib.h"

char toLower(char c) {
    return c >= 'A' && c <= 'Z' ? char(c | 0x20) : c;
}

int main(int argc, char* argv[ ]) {
    setName("compare files bytewise (case-insensitive)");
    registerTestlibCmd(argc, argv);

    int n = 0;

    while (!ans.eof()) {
        quitif(ouf.eof(), _wa, "Unexpected end of file (only %d characters found)", n);

        n++;
        char j = ans.readChar();
        char p = ouf.readChar();
        if (toLower(j) != toLower(p))
            expectedButFound(_wa, j, p, "%d%s characters differ", n, englishEnding(n).c_str());
    }
    quitif(!ouf.eof(), _wa, "Extra information in the output file: %d characters expected", n);

    quitf(_ok, "%d characters", n);
}
