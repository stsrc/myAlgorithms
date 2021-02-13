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

size_t parent(size_t i) {
	return (i - 1) / 2;
}

size_t leftChild(size_t i)
{
	return 2 * i + 1;
}

size_t rightChild(size_t i)
{
	return 2 * i + 2;
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

void checkIsMaxHeap(struct array *array, size_t i)
{
	if (i >= array->size)
		return;

	size_t leftchild = leftChild(i);
	size_t rightchild = rightChild(i);

	if (leftchild < array->size && array->a[leftchild] > array->a[i])
		abort();
	if (rightchild < array->size && array->a[rightchild] > array->a[i])
		abort();

	checkIsMaxHeap(array, leftchild);
	checkIsMaxHeap(array, rightchild);
}

void heapIncreaseKey(struct array *array, size_t i, int key)
{
	if (key < array->a[i])
		return;

	array->a[i] = key;
	while(array->a[parent(i)] < array->a[i]) {
		int temp = array->a[i];
		array->a[i] = array->a[parent(i)];
		array->a[parent(i)] = temp;
		if (parent(i) == 0)
			break;
		i = parent(i);
	}
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
	initArray(&array, 1 + (rand() % 20));

	generateArray(&array);
	buildMaxHeap(&array);
	printArray(&array);
	checkIsMaxHeap(&array, 0);
	heapIncreaseKey(&array, array.size - 1, 100);
	printArray(&array);
	checkIsMaxHeap(&array, 0);
	deinitArray(&array);
	return 0;
}
