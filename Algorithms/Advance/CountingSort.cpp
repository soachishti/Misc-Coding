#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>
using namespace std;

const int SIZE = 11;

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void FillArray(int arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand()%size;
    }
}

void PrintArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void CountingSort(int arr[], int size) {
    // Get largest number
    int k = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > k) 
            k = arr[i];
    }
    k = k+1;
    
    // Make empty array 
    int *C = new int[k];
    for (int i = 0; i < k; i++) {
        C[i] = 0;
    }

    
    // Count Numbers
    for (int i = 0; i < size; i++) {
        C[arr[i]]++;
    }

    // Make Frequency
    for (int i = 1; i < k; i++) {
        C[i] = C[i] + C[i-1];
    }
    
    int *B = new int[size];
    for (int i = 0; i < size; i++) {
        B[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        B[C[arr[i]]-1] = arr[i];
        C[arr[i]]--;
    }    
    PrintArray(B, size);
}

int main() {
    int arr[SIZE] = {0};
    FillArray(arr, SIZE);
    PrintArray(arr, SIZE);
    
    CountingSort(arr, SIZE);
    
    return 0;
}