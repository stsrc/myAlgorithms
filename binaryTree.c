#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct node {
	struct node *parent;
	struct node *left;
	struct node *right;
	int *element;
};

struct node * init_node(int value, struct node *parent) {
	struct node *ptr = calloc(1, sizeof(struct node));
	ptr->element = calloc(1, sizeof(int));
	*(ptr->element) = value;
	ptr->parent = parent;
	return ptr;
}

void deinit_node(struct node *ptr)
{
	free(ptr->element);
	free(ptr);
}

void add(struct node *root, int value) {
	if (*root->element == value)
		abort();

	if (*root->element > value) {
		if (!root->left) {
			root->left = init_node(value, root);
			return;
		} else {
			add(root->left, value);
		}
	} else {
		if (!root->right) {
			root->right = init_node(value, root);
			return;
		} else {
			add(root->right, value);
		}
	}
}

struct node * search(struct node *root, int value) {
	if (*root->element == value) {
		return root;
	} else if (*root->element > value && root->left) {
		return search(root->left, value);
	} else if (*root->element <= value && root->right) {
		return search(root->right, value);
	} else {
		return NULL;
	}
}

struct node * lowest(struct node *root) {
	if (root->left)
		root = lowest(root->left);

	return root;
}
#include <assert.h>

struct node * removeNode(struct node *root, int value) {
	struct node *toRemove = search(root, value);
	struct node *newRoot = root;
	if (!toRemove) {
		return newRoot;
	}

	if (!toRemove->left && !toRemove->right) {
		if (toRemove->parent->left == toRemove) {
			toRemove->parent->left = NULL;
		} else {
			toRemove->parent->right = NULL;
		}
		deinit_node(toRemove);
	} else if (toRemove->left && !toRemove->right) {
		toRemove->left->parent = toRemove->parent;
		if (toRemove->parent->left == toRemove) {
			toRemove->parent->left = toRemove->left;
		} else {
			toRemove->parent->right = toRemove->left;
		}
		deinit_node(toRemove);
	} else if (!toRemove->left && toRemove->right) {
		toRemove->right->parent = toRemove->parent;
		if (toRemove->parent->left == toRemove) {
			toRemove->parent->left = toRemove->right;
		} else {
			toRemove->parent->right = toRemove->right;
		}
		deinit_node(toRemove);
	} else {
		struct node *element = lowest(toRemove->right);
		assert(element);

		if (element->parent->left == element) {
			element->parent->left = NULL;
		} else {
			element->parent->right = NULL;
		}

		element->left = toRemove->left;
		element->right = toRemove->right;
		element->parent = toRemove->parent;

		toRemove->left->parent = element;
		toRemove->right->parent = element;

		if(toRemove->parent->left == toRemove) {
			toRemove->parent->left = element;
		} else {
			toRemove->parent->right = element;
		}

		deinit_node(toRemove);
	}

	return newRoot;
}

int maxdeep(struct node *root) {
	int deepleft = 0, deepright = 0;

	if (!root)
		return 0;

	if (root->left == NULL && root->right == NULL) {
		return 1;
	}

	if (root->left) {
		deepleft += 1 + maxdeep(root->left);
	}

	if (root->right) {
		deepright += 1 + maxdeep(root->right);
	}

	return deepleft > deepright? deepleft : deepright;
}

void getElementsAtDeep(struct node *root, int level, int currentLevel, int **output, size_t *count) {
	if (level == currentLevel) {
		*output = realloc(*output, (*count) + 1);
		(*output)[*count] = *root->element;
		(*count)++;
		return;
	} else {
		if (root->left)
			getElementsAtDeep(root->left, level, currentLevel + 1, output, count);
		if (root->right)
			getElementsAtDeep(root->right, level, currentLevel + 1, output, count);
	}
}

void printtree(struct node *root)
{
	int maxDeep = maxdeep(root);
	for (int i = 1; i <= maxDeep; i++) {
		int *output = NULL;
		size_t count = 0;
		getElementsAtDeep(root, i, 1, &output, &count);
		for (size_t j = 0; j < count; j++) {
			printf("%d", output[j]);
			printf(" ");
		}
		printf("\n");
		free(output);
	}

}

int main(void)
{
	struct node *root = init_node(50, NULL);
	add(root, 25);
	add(root, 20);
	add(root, 30);
	add(root, 100);
	add(root, 75);
	add(root, 110);
	add(root, 33);
	add(root, 108);
	printtree(root);
	printf("---\n");
	root = removeNode(root, 100);
	printtree(root);
	return 0;
}
