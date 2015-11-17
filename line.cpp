#include "testlib.h"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[ ]) {
    setName("compare lines of text");
    registerTestlibCmd(argc, argv);

    size_t n = 0;
    string p, j, a, b;
    while (!ouf.eof() && !ans.eof()) {
        ouf.readLineTo(p);
        ans.readLineTo(j);
        n++;

        istringstream ps(p), js(j);
        bool match = true;
        p.clear();
        j.clear();

        while (ps >> a && js >> b) {
            if (a != b)
                match = false;
            p += a;
            p += ' ';
            j += b;
            j += ' ';
        }

        while (ps >> a) {
            match = false;
            p += a;
            p += ' ';
        }

        while (js >> b) {
            match = false;
            j += b;
            j += ' ';
        }

        if (!match) {
            if (!p.empty())
                p.resize(p.size() - 1);
            if (!j.empty())
                j.resize(j.size() - 1);
            p = compress(p);
            j = compress(j);
            string ending = englishEnding(n);
            quitf(_wa, "%d%s lines differ: expected \"%s\", found \"%s\"",
                n, ending.c_str(), j.c_str(), p.c_str()
            );
        }
    }

    while (!ouf.eof()) {
        ouf.readLineTo(p);
        istringstream ss(p);
        if (ss >> a)
            quit(_wa, "Participant's output contains extra lines");
    }

    while (!ans.eof()) {
        ans.readLineTo(j);
        istringstream ss(j);
        if (ss >> b)
            quit(_wa, "Unexpected EOF in the participant's output");
    }

    quitif(n != 1, _ok, "%d lines", n);
    quit(_ok, "1 line");
}
