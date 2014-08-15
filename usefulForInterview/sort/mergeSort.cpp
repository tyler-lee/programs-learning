#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;
using std::cin;

void print(const int*, int);
void mergeSort(const int*, int, int, int*);

int main() {
	int	unsort[] = {4,14,2,1,6,3,7,9,5};
	int size = sizeof(unsort) / sizeof(int);

	int* sorted = new int[size];
	assert(sorted != NULL);

	mergeSort(unsort, 0, size, sorted);

	print(unsort, size);
	print(sorted, size);
}

void print(const int* items, int size) {
	for(int i=0; i<size; i++) {
		std::cout << *(items+i) << "\t";
	}
	std::cout << std::endl;
}

void merge(const int* unsort, int first, int mid, int last, int* sorted) {
	int i = first;
	int j = mid;
	int index = first;

	while(i<mid && j<last) {
		if(unsort[i]<unsort[j]) {
			sorted[index++] = unsort[i++];
		}
		else {
			sorted[index++] = unsort[j++];
		}
	}

	while(i<mid) {
		sorted[index++] = unsort[i++];
	}
	while(j<last) {
		sorted[index++] = unsort[j++];
	}
}

void mergeSort(const int* unsort, int first, int last, int* sorted) {
	if(first+1 < last) {
		int mid = (first + last) / 2;
		mergeSort(unsort, first, mid, sorted);
		mergeSort(unsort, mid, last, sorted);
		merge(unsort, first, mid, last, sorted);
	}
}
