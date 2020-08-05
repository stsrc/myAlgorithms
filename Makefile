all: quicksort.c
	gcc -std=gnu99 -Wall quicksort.c -o quicksort

clean:
	rm quicksort
