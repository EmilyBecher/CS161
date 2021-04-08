#include <iostream>

using namespace std;

int* create_mem1(int size);
void create_mem2(int** ptr_arr, int size);
void create_mem3(int*& ptr_arr, int size);

int main() {
	int* arr1 = create_mem1(5);
	
	int* arr2;
	create_mem2(&arr2, 10);
	
	int* arr3;
	create_mem3(arr3, 20);

	delete [] arr1;
	delete [] arr2;
	delete [] arr3;

	arr1 = NULL;
	arr2 = NULL;
	arr3 = NULL;

	return 0;
}

//create memory
int* create_mem1(int size) {
	int* arr = new int[size];

	return arr;
}

void create_mem2(int** ptr_arr, int size) {
	*ptr_arr = new int[size];
}

void create_mem3(int*& ptr_arr, int size) {
	ptr_arr = new int[size];
}
