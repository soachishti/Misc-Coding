#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    register int a = 1000;
    
    const int size = 10;
    int A[size] = {0};
    
    // Fill data 
    for (int i = 0; i < size; i++) 
        A[i] = rand() % size;
    
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size-i; j++) {
            if (A[j] > A[j+1])
                swap(A[j+1], A[j]);
        }
    }
    
    for (int i = 0; i < size; i++) 
        cout << A[i] << " ";
}