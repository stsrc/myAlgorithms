#include <stdio.h>
#include <stdlib.h>

void printArray(int *toSort, int count) {
	for (int j = 0; j < count; j++) {
		printf(" toSort[%d] = %d", j, toSort[j]);
	}
	printf("\n");
}

void quicksort(int *toSort, int count) {
	if (count <= 1)
		return;

	int pivot = count / 2;
	int temp = toSort[count - 1];
	toSort[count - 1] = toSort[pivot];
	toSort[pivot] = temp;
	int j = 0;

	for (int i = 0; i < count; i++) {
		if (toSort[i] < toSort[count - 1]) {
			temp = toSort[j];
			toSort[j] = toSort[i];
			toSort[i] = temp;
			j++;
		}
	}

	temp = toSort[count - 1];
	toSort[count - 1] = toSort[j];
	toSort[j] = temp;

	quicksort(toSort, j);
	quicksort(toSort + j, count - j);
}

void check(int *toSort, int *sorted, int count)
{
	for (int i = 0; i < count; i++) {
		if (toSort[i] != sorted[i]) {
			printf("FAIL: toSort[%d] = %d, sorted[%d] = %d!\n",
			      i, toSort[i], i, sorted[i]);

			for (int j = 0; j < count; j++) {
				printf(" toSort[%d] = %d", j, toSort[j]);
			}
			printf("\n");
			abort();
		} else {
			printf("OK: toSort[%d] = %d, sorted[%d] = %d!\n",
			      i, toSort[i], i, sorted[i]);
		}
	}
}

int main(void) {
	int count = 10;
	int toSort[10] = {1, 7, 3, 6, 9, 11, 0, 8, 2, 12};
	int sorted[10] = {0, 1, 2, 3, 6, 7, 8, 9, 11, 12};

	quicksort(toSort, count);
	check(toSort, sorted, count);
}
