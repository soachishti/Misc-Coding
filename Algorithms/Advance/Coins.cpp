// Task is to find least possible changes to get the money.
// For example break money in to changes. (Bank System)

#include <iostream>
using namespace std;

int main() {
    int money = 101;
    const int SIZE = 5;
    int change[SIZE] = {1, 2, 5, 10, 20};
    int total = 0;
    for (int i = SIZE-1; i >= 0; i--) {
        if (change[i]+total <= money) {
            cout << "Index#" << i << ": " << change[i] << endl;
            total += change[i];
        }
        if (total < money && change[i]+total <= money) {
            
            i++;
        }
    }
    cout << "Total: " << total << endl;
}