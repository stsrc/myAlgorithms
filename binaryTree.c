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

void replaceInParent(struct node *node, struct node *newElement)
{
	if (node->parent) {
		if (node == node->parent->left) {
			node->parent->left = newElement;
		} else if (node == node->parent->right) {
			node->parent->right = newElement;
		}
	}
	if (newElement) {
		newElement->parent = node->parent;
	}
}

struct node *removeNode(struct node *root, int value) {
	if (!root)
		return NULL;

	struct node *toRemove = search(root, value);

	if (toRemove->left && toRemove->right) {
		struct node *successor = lowest(toRemove->right);
		*toRemove->element = *successor->element;
		removeNode(toRemove->right, *successor->element);
	} else if (toRemove->left) {
		replaceInParent(toRemove, toRemove->left);
		if (toRemove == root)
			root = toRemove->left;
		deinit_node(toRemove);
	} else if (toRemove->right) {
		replaceInParent(toRemove, toRemove->right);
		if (toRemove == root)
			root = toRemove->right;
		deinit_node(toRemove);
	} else {
		if (toRemove == root)
			root = NULL;
		replaceInParent(toRemove, NULL);
		deinit_node(toRemove);
	}

	return root;
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
	if (!root)
		return;

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
	struct node *root = init_node(5, NULL);
	add(root, 4);
	add(root, 10);
	add(root, 12);
	add(root, 7);
	add(root, 8);
	add(root, 9);
	add(root, 11);
	printtree(root);
	printf("---\n");
	root = removeNode(root, 12);
	printtree(root);
	return 0;
}
