#include <iostream>
#include <string.h>
using namespace std;

int Hash(string str) {
    int hashVal = 0;
    for (int i = 0; i < str.size(); i++) {
        hashVal += (char)str[i];
    }
    return hashVal;
}

int RabinKarp(string t, string p) {
    int pHash = Hash(p);
    int limit = t.size() - p.size() + 1;
    for (int i = 0; i < limit; i++) {
        string substr = t.substr(i, p.size());
        int tHash = Hash(substr);
        if (pHash == tHash && p == substr) return i;
    }
    return -1;
}

int main() {
    cout << RabinKarp("hello world", "llo") << endl;
}