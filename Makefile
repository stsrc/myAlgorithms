all: quicksort.c
	gcc -std=gnu99 -Wall quicksort.c -o quicksort
	gcc -std=gnu99 -Wall binaryTree.c -o binaryTree

clean:
	rm quicksort
