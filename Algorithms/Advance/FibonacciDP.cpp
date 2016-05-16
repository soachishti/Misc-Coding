#include <iostream>
#include <cstdlib>
using namespace std;

int *store;

int IterFib(int n) {
    int a = 1;
    int b = 1;
    int c = 0;
    for (int i = 0; i < n; i++) {
        c = a+b;
        a = b;
        b = c;
    }
    return store[n];
}    

int FibDP(int n) {
    if (n < 2) 
        return n;
    if (store[n] == 0)
        store[n] = FibDP(n-1) + FibDP(n-2);
    return store[n];
    
}

int main() {
    int num = 6;
    store = new int[num+1];
    for (int i = 0; i <= num; i++) store[i] = 0;
    cout << "FibDP: " << FibDP(num) << endl;
    cout << "IterFib: " << IterFib(num) << endl;
}