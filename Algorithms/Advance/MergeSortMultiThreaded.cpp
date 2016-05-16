#include <iostream>
#include <math.h>
#include <algorithm>
#include <ctime>
using namespace std;

void fill(int list[], int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		list[i] = rand() % 100 + 10;
	}
}

void print(int list[], int size) {
	for (int i = 0; i < size; i++) {
		cout << list[i] << " ";
	}
	cout << endl;
}

void MergeSort(int list[], int start, int end, int mid) {
	int size = end - start + 1;
	int *tmp = new int[size];
	int tmpIndex = 0;

	int left = start;
	int right = mid + 1;

	// Getting sorted data from 
	while(left <= mid && right <= end) {
		if (list[left] > list[right]) {		
			tmp[tmpIndex] = list[right];
            right++;
        }
		else {
			tmp[tmpIndex] = list[left];
            left++;
        }
        tmpIndex++;
	}

	// Dealing with remaing element in array
	while (left <= mid) 
		tmp[tmpIndex++] = list[left++];
	
	while (right <= end)
		tmp[tmpIndex++] = list[right++];
	
	// Putting sorted data into array
	for (int i = start, tmpIndex = 0; i <= end; i++, tmpIndex++) 
		list[i] = tmp[tmpIndex];
	
	delete[] tmp;
}

void MergeSortSplit(int list[], int start, int end) {
	if (start < end) {
		int mid = (end + start) / 2;        
		MergeSortSplit(list, start, mid);   
		MergeSortSplit(list, mid + 1, end); 
		MergeSort(list, start, end, mid);
	}
}


int main() {
    int threads = 4;

    int total = 10010;
    int partitionSize = ceil(total/threads); 
    int start = 0;
    int endV = partitionSize;
    while (total > 0) {
        cout << start <<  "\t" << endV << endl;
        start = endV+1;
        total -= partitionSize;
        if (total > partitionSize) {
            endV = endV + partition;            
        }
        else {
            endV = endV + total;
        }
        
    }
    
    return 0;
	const int size = 10;
	int list[size];
	fill(list, size);
	MergeSortSplit(list, 0, size-1);
	print(list, size);

	return 0;
}