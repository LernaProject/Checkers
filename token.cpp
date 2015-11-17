#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[ ]) {
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = 0;
    string j, p;
    while (!ans.seekEof() && !ouf.seekEof()) {
        n++;
        ans.readTokenTo(j);
        ouf.readTokenTo(p);
        
        if (j != p) {
            j = compress(j);
            p = compress(p);
            string ending = englishEnding(n);
            quitf(_wa, "%d%s words differ: expected \"%s\", found \"%s\"",
                n, ending.c_str(), j.c_str(), p.c_str()
            );
        }
    }

    if (ans.seekEof())
        if (ouf.seekEof())
            if (n == 1) {
                j = compress(j);
                quitf(_ok, "\"%s\"", j.c_str());
            } else
                quitf(_ok, "%d tokens", n);
        else
            quitf(_wa, "Participant's output contains extra tokens");
    else
        quitf(_wa, "Unexpected EOF in the participant's output");
}
