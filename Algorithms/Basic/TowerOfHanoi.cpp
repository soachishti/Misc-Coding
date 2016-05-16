#include <iostream>
using namespace std;

void tower(int count, char a, char b, char c) {
    if (count == 0) {
        cout << a << " " << b << " " << c << endl;
    }
    else {
        tower(count-1, a, c, b);
        cout << a << " " << b << " " << c << endl;
        tower(count-1, b, c, a);
    }
}

int main() {
    tower(5, 'A', 'B', 'C');
}