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

int Left(int i) {
    return 2*i;
}

int Right(int i) {
    return (2 * i) + 1;
}

void MaxHeapify(int arr[], int i = 1) {
    int largest = i;
    int l = Left(i);
    int r = Right(i);
    if (l < SIZE && arr[l] > arr[i]) 
        largest = l;
    
    if (r < SIZE && arr[r] > arr[largest])
        largest = r;
        
    if (largest != i) {
        swap(arr[i], arr[largest]);
        MaxHeapify(arr, largest);
    }
}

void BuildMaxHeap(int arr[]) {
    for (int i = SIZE/2; i >= 1; i--) {
        MaxHeapify(arr, i);
    }
}

void HeapSort(int arr[]) {
    BuildMaxHeap(arr);
    for (int i = SIZE-1; i >= 2; i--) {
        //PrintArray(arr, SIZE);
        swap(arr[1], arr[i]);
        SIZE = SIZE - 1;
        MaxHeapify(arr, 1);
    }    
}

int main() {
    const int SIZE = 11;
    int arr[SIZE] = {0};
    FillArray(arr, SIZE);
    PrintArray(arr, SIZE);
    
    BuildMaxHeap(arr); // Working
    HeapSort(arr);
    PrintArray(arr, 11);
    
    return 0;
}