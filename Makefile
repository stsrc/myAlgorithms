all: quicksort.c binaryTree.c
	gcc -std=gnu99 -Wall binaryTree.c -o binaryTree
	gcc -std=gnu99 -Wall quicksort.c -o quickSort

clean:
	rm quicksort
