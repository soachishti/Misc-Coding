// Name: Syed Owais Ali Chishti
// Roll no: p146011
// Section: A
// Task: You have the two sorted lists of N/2 elements each. Find the median N numbers 
//       when two lists are combined. Suggest an  efficient algorithm for solving the
//       problem and give its analysis (Recurrence Relation / Asymptotic notation etc...)
// Running Time: Theta(n)

#include <iostream>
using namespace std;

void Combine(int Store[], int ArrA[], int ArrB[], int SizeA, int SizeB) {
    int a, b, i;
    a = b = i = 0;
    while (a < SizeA && b < SizeB) {
        if (ArrA[a] < ArrB[b]) Store[i++] = ArrA[a++];
        else Store[i++] = ArrB[b++];
    }
    while (a < SizeA) Store[i++] = ArrA[a++];
    while (b < SizeB) Store[i++] = ArrB[b++];
}

int main () {
    int SizeA = 5;
    int SizeB = 5;
    int Total = SizeA + SizeB;
    int ArrA[] = {80, 85, 86, 87, 100};
    int ArrB[] = {2, 60, 69, 70, 86};
    int *Store = new int[SizeA+SizeB+1];
    Combine(Store, ArrA, ArrB, SizeA, SizeB);
    for (int i = 0 ; i < Total; i++) cout << Store[i] << " "; 
    cout << endl << "Median: ";
    if (Total % 2 == 0) cout << Store[(Total/2) - 1] << " " << Store[Total/2];
    else cout << Store[Total/2];
    cout << endl;
}