all: quicksort.c binaryTree.c
	gcc -std=gnu99 -Wall binaryTree.c -o binaryTree
	gcc -std=gnu99 -Wall quicksort.c -o quickSort
	gcc -std=gnu99 -Wall heapsort.c -o heapsort
	gcc -std=gnu99 -Wall priority-queue.c -o priority-queue
clean:
	rm quickSort binaryTree
