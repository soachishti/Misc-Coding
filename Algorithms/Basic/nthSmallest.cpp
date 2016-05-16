// Wrong result when same element.
// Count same element as one
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int GreaterAfter(int arr[], int val, int arrSize) {
    int next = 0x0FFFFFFF;
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] > val && next > arr[i]) {
            next = arr[i];
        }
    }    
    return next;
}

void nthMin(int arr[], int n, int arrSize) {
    int min = arr[0];
    // Find first min
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }    
    
    for (int i = 1; i < n; i++) {
        min = GreaterAfter(arr, min, arrSize);
    }
    cout << min;
}

int main () {
    srand(time(NULL));
    const int SizeA = 10;
    int ArrA[SizeA] = {0};
    for (int i = 0; i < SizeA; i++) {
        ArrA[i] = rand()%10;
        cout << ArrA[i] << " ";
    }
    cout << endl;
    //int ArrA[] = {1,2,3,4,5,6,7,8,9, 0};
    nthMin(ArrA, 5, SizeA);
    return 0;
}