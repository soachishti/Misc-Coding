#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>
using namespace std;

int SIZE = 11;

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void FillArray(int arr[], int size) {
    srand(time(NULL));
    for (int i = 1; i < size; i++) {
        arr[i] = rand()%size;
    }
}

void PrintArray(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int Partition(int arr[], int p, int r) {
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j <= (r-1); j++) {
        if (arr[j] <= x) {
            i = i + 1;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[r]);
    return i+1;
} 

void QuickSort(int arr[], int p, int r) {
    if (p < r) {
        PrintArray(arr, SIZE);
        int q = Partition(arr,p,r);
        QuickSort(arr, p, q-1);
        QuickSort(arr, q+1, r);
    }    
}

int main() {
    const int SIZE = 11;
    int arr[SIZE] = {0};
    FillArray(arr, SIZE);
    PrintArray(arr, SIZE);
    
    QuickSort(arr, 1, SIZE);
    PrintArray(arr, SIZE);
    
    return 0;
}