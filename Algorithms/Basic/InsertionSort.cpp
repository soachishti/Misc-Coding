#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    register int a = 1000;
    
    const int size = 10;
    int A[size] = {0};
    
    // Fill random data 
    for (int i = 0; i < size; i++) 
        A[i] = rand() % size;
    
    for(int j = 0; j < size; j++) {
        int key = A[j];
        int i = j - 1;
        while (i > 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
    
    for (int i = 0; i < size; i++) 
        cout << A[i] << " ";
}
