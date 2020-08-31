#include <functional>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

namespace kmp {

// All arrays use 0-based indexes.

string segment, pattern;

const int MAX_SIZE = 1000009;
int nxt[MAX_SIZE];

/**
 * Ordinary KMP preprocess.
 */
void preprocess() {
    // https://blog.csdn.net/yutianzuijin/article/details/11954939
    nxt[0] = nxt[1] = 0;
    int cnd = 0;
    for (int pos = 1; pos < (int)pattern.size(); pos++) {
        while (cnd > 0 && pattern[pos] != pattern[cnd]) {
            cnd = nxt[cnd];
        }
        if (pattern[cnd] == pattern[pos]) {
            cnd++;
        }
        nxt[pos + 1] = cnd;
    }
}

/**
 * Another KMP preprocess, more optimized than previous one.
 */
void preprocess_alternative() { // Wikipedia
    nxt[0] = -1;
    int cnd = 0;
    int pos = 1;
    int sz = pattern.size();
    while (pos < sz) {
        if (pattern[cnd] == pattern[pos]) {
            nxt[pos] = nxt[cnd];
        } else {
            nxt[pos] = cnd;
            while (cnd >= 0 && pattern[pos] != pattern[cnd]) {
                cnd = nxt[cnd];
            }
        }
        pos++, cnd++;
    }
    nxt[pos] = cnd;
}

void print_next() {
    int sz = pattern.size();
    for (int i = 0; i <= sz; i++) {
        cout << setw(2) << nxt[i] << ' ';
    }
    cout << endl;
}

/**
 * Match kmp::pattern against kmp::segment (find kmp::pattern in kmp::segment).
 * Whenever a full match is found, the function parameter `callback` will be
 * called with one `int` argument indicating the 0-based index of the beginning
 * of the full match.
 */
void match(function<void(int)> callback) {
    int sz = segment.size();
    int psz = pattern.size();
    int ppos = 0; // pattern position
    for (int i = 0; i < sz; i++) {
        while (ppos > 0 && segment[i] != pattern[ppos]) {
            ppos = nxt[ppos];
        }
        if (pattern[ppos] == segment[i]) {
            ppos++;
        }
        if (ppos == psz) {
            callback(i - ppos + 1); // 0-based
            ppos = nxt[ppos];
        }
    }
}

} // namespace kmp

int main() {
    cin >> kmp::segment >> kmp::pattern;
    kmp::preprocess();
    kmp::print_next();
    kmp::preprocess_alternative();
    kmp::print_next();
    kmp::match([](int idx) { cout << idx + 1 << endl; });
}