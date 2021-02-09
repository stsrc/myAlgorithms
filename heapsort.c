#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct array {
	int *a;
	size_t size;
};

void initArray(struct array *array, size_t size)
{
	array->a = calloc(1, size * sizeof(int));
	array->size = size;
}

void deinitArray(struct array *array)
{
	free(array->a);
	array->a = NULL;
	array->size = 0;
}

void printArray(struct array *array)
{
	for (size_t i = 0; i < array->size; i++) {
		printf("a[%ld] = %d; ", i, array->a[i]);
	}
	printf("\n");
}

size_t parentOfI(size_t i)
{
	return i/2;
}

size_t leftChild(size_t i)
{
	return 2 * i;
}

size_t rightChild(size_t i)
{
	return 2 * i + 1;
}


int maxHeapify(struct array *array, size_t i)
{
	size_t leftCh = leftChild(i);
	size_t rightCh = rightChild(i);
	size_t largest = 0;
	if (leftCh < array->size && array->a[leftCh] > array->a[i]) {
		largest = leftCh;
 	} else {
		largest = i;
	}

	if (rightCh < array->size && array->a[rightCh] > array->a[largest]) {
		largest = rightCh;
	}

	if (largest != i) {
		int temp = array->a[i];
		array->a[i] = array->a[largest];
		array->a[largest] = temp;
		maxHeapify(array, largest);
	}

	return 0;
}

int buildMaxHeap(struct array *array)
{
	const size_t halfOfArraySize = array->size / 2;
	for (size_t i = halfOfArraySize; i <= halfOfArraySize; i--) {
		maxHeapify(array, i);
	}

	return 0;
}

void heapsort(struct array *array)
{
	printArray(array);
	buildMaxHeap(array);
	printArray(array);
	size_t size = array->size;
	for (size_t i = array->size - 1; i >= 1; i--) {
		int temp = array->a[0];
		array->a[0] = array->a[i];
		array->a[i] = temp;

		array->size--;
		maxHeapify(array, 0);
	}
	array->size = size;
	printArray(array);
}

void generateArray(struct array *array)
{
	for (size_t i = 0; i < array->size; i++) {
		array->a[i] = rand() % array->size;
	}
}

int main(void)
{
	time_t t;
	srand((unsigned) time(&t));

	struct array array;
	initArray(&array, rand() % 20);

	generateArray(&array);

	heapsort(&array);

	deinitArray(&array);
	return 0;
}
