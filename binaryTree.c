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

struct node * removeNode(struct node *root, int value) {
	struct node *toRemove = search(root, value);
	struct node *newRoot = root;
	if (!toRemove) {
		return newRoot;
	}

	if (!toRemove->left && !toRemove->right) {
		goto end;
	} else if (!toRemove->left) {
		if (toRemove->parent) {
			if (toRemove->parent->left == toRemove) {
				toRemove->right->parent = toRemove->parent;
				toRemove->parent->left = toRemove->right;
			} else {
				toRemove->right->parent = toRemove->parent;
				toRemove->parent->right = toRemove->right;
			}
		} else {
			newRoot = toRemove->right;
			toRemove->right->parent = NULL;
		}
	} else if (!toRemove->right) {
		if (toRemove->parent) {
			if (toRemove->parent->left == toRemove) {
				toRemove->left->parent = toRemove->parent;
				toRemove->parent->left = toRemove->left;
			} else {
				toRemove->right->parent = toRemove->parent;
				toRemove->parent->right = toRemove->left;
			}
		} else {
			newRoot = toRemove->left;
			toRemove->left->parent = NULL;
		}
	} else {
		if (toRemove->parent) {
			if (toRemove == toRemove->parent->left) {
				toRemove->parent->left = toRemove->right; //ok
				toRemove->right->parent = toRemove->parent; //ok
				struct node *temp = toRemove->right;
				while(temp->left != NULL) {
					temp = temp->left;
				}
				temp->left = toRemove->left;
				toRemove->left->parent = temp;
			} else if (toRemove == toRemove->parent->right) {
				toRemove->parent->right = toRemove->right; //ok
				toRemove->right->parent = toRemove->parent; //ok
				struct node *temp = toRemove->right;
				while(temp->left != NULL) {
					temp = temp->left;
				}
				temp->left = toRemove->left;
				toRemove->left->parent = temp;
			}
		} else {
			toRemove->right->parent = NULL;
			struct node *temp = toRemove->right;
			while (temp->left != NULL)
				temp = temp->left;
			temp->left = toRemove->left;
			toRemove->left->parent = temp;
		}
	}

end:
	deinit_node(toRemove);
	return newRoot;
}

int maxdeep(struct node *root) {
	int deepleft = 0, deepright = 0;

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

void printtree_level(struct node *root, int level, int max_deep) {
	int spaces = 10;
	for (int i = 0; i < spaces; i++)
		printf(" ");
	printf("%d", *root->element);
	for (int i = 0; i < spaces; i++)
		printf(" ");
}
void printtree(struct node *root)
{
	int maxDeep = maxdeep(root);

}

int main(void)
{
	struct node *root = init_node(50, NULL);
	add(root, 60);
	add(root, 70);
	add(root, 80);
	assert(maxdeep(root) == 4);
	add(root, 65);
	assert(maxdeep(root) == 4);
	return 0;
}
