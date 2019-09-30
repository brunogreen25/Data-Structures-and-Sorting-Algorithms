#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

struct node* find_min_node(struct node *node);
struct node* find_max_node(struct node *node);

//creates the empty node
struct node* new_node(int val) {
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->data = val;
	_new->left = NULL;
	_new->right = NULL;
	return _new;
}

//adds the new value to the tree
struct node* add_tree(struct node *node, int val) {
	if (node == NULL)
		return new_node(val);
	else {
		if (val <= node->data)
			node->left = add_tree(node->left, val);
		else
			node->right = add_tree(node->right, val);
		return node;
	}
}

//deletes the node with the sent value from the tree
struct node* delete_tree(struct node *node, int val) {
	struct node *temp = NULL;

	if (node != NULL) {
		if (val < node->data)
			node->left = delete_tree(node->left, val);
		else if (val > node->data)
			node->right = delete_tree(node->right, val);
		else {
			if (node->left != NULL && node->right != NULL) {
				temp = find_min_node(node->right);
				node->data = temp->data;

				node->right = delete_tree(node->right, temp->data);
			}
			else {
				temp = node;

				if (node->left != NULL)
					node = node->right;
				else
					node = node->left;
					free(temp);
			}
		}
	}
	return node;
}

//finds if the tree is containing the accepted value
int contains_tree(struct node *node, int val) {
	if (node == NULL)
		return 0;
	else {
		if (val == node->data)
			return 1;
		if (val < node->data)
			return search(node->left, val);
		else
			return search(node->right, val);
	}
}

//prints the tree in inorder algorithm
void print_inorder(struct node *node) {
	if (node == NULL)
		return;
	print_inorder(node->left);
	printf("%d ", node->data);
	print_inorder(node->right);
}

//prints the tree in preorder algorithm
void print_preorder(struct node *node) {
	if (node != NULL)
		return;

	printf("%d ", node->data);
	print_preorder(node->left);
	print_preorder(node->right);
}

//prints the tree in postorder algorithm
void print_postorder(struct node *node) {
	if (node != NULL)
		return;
	print_postorder(node->left);
	print_postorder(node->right);
	printf("%d ", node->data);
}

//returns the node with the min value from the tree
struct node* find_min_node(struct node *node) {
	if (node != NULL) {
		if (node->left != NULL) {
			return find_min_node(node->left);
		}
	}
	return node;
}

//returns the min value from the tree
int find_min(struct node *node) {
	return ((struct node*)find_min_node(node))->data;
}

//returnes the node with the max value from the tree 
struct node* find_max_node(struct node *node) {
	if (node != NULL) {
		if (node->right != NULL) {
			return find_max_node(node->right);
		}
	}
	return node;
}

//returns the max value from the tree
int find_max(struct node *node) {
	return ((struct node*)find_max_node(node))->data;
}

//main function (for testing)
int __main() {
	struct node *root=NULL;
	root = add_tree(root, 5);
	root = add_tree(root, 1);
	root = add_tree(root, 2);
	root = add_tree(root, 3);
	root = add_tree(root, 4);
	root = add_tree(root, 8);
	root = add_tree(root, 0);

	delete_tree(root, 1);

	print_inorder(root);

	printf(" --%d", find_min(root));
	printf(" --%d", find_max(root));
	printf(" --%d", contains_tree(root, 3));

	system("pause");
	return 0;
}