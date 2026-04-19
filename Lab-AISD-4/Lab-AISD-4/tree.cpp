#include "tree.h"
#include <stdio.h>
#include <stdlib.h>


void fixInsertion(node* tree,bool is_root) {
	if (is_root) {
		tree->color = 2;
		return;
	}
	while (tree->parent->color == 1) {
		if (tree->parent->left == tree) {
			if (tree->parent->parent != NULL && ((tree->parent->parent->left != NULL && tree->parent->parent->left != tree->parent && tree->parent->parent->left->color == 1) || (tree->parent->parent->right != NULL && tree->parent->parent->right != tree->parent && tree->parent->parent->right->color == 1))) {
				//есть красный дядя
				tree->parent->parent->color = 2;
				if (tree->parent->parent->left != NULL && tree->parent->parent->left != tree->parent)
					tree->parent->parent->left->color = 2;
				else
					tree->parent->parent->right->color = 2;
			}
			else {
				if()
			}
		}
		else {

		}
	}
}


void insert(tree* tree, int value) {

	node* t = (node*)malloc(sizeof(node));
	t->color = 1;//red
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	bool is_root = 1;

	if (tree == NULL) {
		tree->root = t;
		tree->root->parent = NULL;
	}
	else {
		node* p = tree->root;
		node* q = NULL;

		while(p != NULL){
			q = p;
			if (p->value < t->value)
				p = p->right;
			else
				p = p->left;
		}
		t->parent = q;
		if (q->value < t->value)
			q->right = t;
		else
			q->left = t;
		is_root = 0;
	}
	fixInsertion(t, is_root);
}

void add_el(tree* t, int value) {
	if (t->root == NULL) {
		t->size++;
		node* n = (node*)malloc(sizeof(node));
		if (n != NULL) {
			n->value = value;
			n->depth = 0;
			n->left = NULL;
			n->right = NULL;
			t->root = n;
		}
		return;
	}
	else {
		t->size++;
		insert(t, value);
	}
}

void print(tree* tree) {
	node** arr = (node**)malloc(sizeof(node*) * tree->size);
	int pos = 0;
	int pos_last = 1;
	int last_depth = 0;

	if (arr != NULL && tree->size > 0) {
		arr[0] = tree->root;

		while (pos < tree->size) {
			if (arr[pos] != NULL) {
				if (last_depth != arr[pos]->depth) {
					printf("\n");
				}
				printf("%d    ", arr[pos]->value);
				last_depth = arr[pos]->depth;

				if (arr[pos]->left != NULL) {
					arr[pos_last] = arr[pos]->left;
					pos_last++;
				}
				if (arr[pos]->right != NULL) {
					arr[pos_last] = arr[pos]->right;
					pos_last++;
				}
			}
			pos++;
		}
		if (arr != NULL)
			free(arr);
	}
}

void add_to_tree_from_branch_min(tree* t, node* el) {
	if (el != NULL && el->left != NULL) {
		if (el->left != NULL && el->left->left != NULL)
			add_to_tree_from_branch_min(t, el->left);
		else if (el->left->left == NULL) {
			node* old = el->left;
			el->left = el->left->right;
			add_el(t, old->value);
			free(old);
			t->size--;
		}
	}
}

void delete_value(tree* t, int value) {
	node* el = t->root;
	if (el != NULL) {
		if (el->value == value) {
			node* l = el->left;
			node* r = el->right;

			if (el != NULL)
				free(el);
			t->root = NULL;
			t->size = 0;

			if (r != NULL) {
				if (l != NULL)
					add_to_tree_from_branch_min(t, r);
				if (t->root != NULL)
					t->root->right = r;
				else
					t->root = r;
			}

			if (l != NULL) {
				if (t->root != NULL)
					t->root->left = l;
				else
					t->root = l;
			}


		}
		else {
			while (1) {
				if (el->left != NULL && el->left->value == value)
					break;
				else if (el->right != NULL && el->right->value == value)
					break;
				else if (el->value > value && el->left != NULL)
					el = el->left;
				else if (el->value < value && el->right != NULL)
					el = el->right;
				else
					break;
			}
			if (el->left != NULL && el->left->value == value) {

				node* l = el->left->left;
				node* r = el->left->right;

				free(el->left);
				el->left = NULL;

				if (r != NULL) {
					if (l != NULL)
						add_to_tree_from_branch_min(t, r);
					if (el->left != NULL)
						el->left->right = r;
					else
						el->left = r;
				}

				if (l != NULL) {
					if (el->left != NULL)
						el->left->left = l;
					else
						el->left = l;
				}

				t->size--;
			}
			else if (el->right != NULL && el->right->value == value) {
				node* l = el->right->left;
				node* r = el->right->right;

				free(el->right);
				el->right = NULL;

				if (r != NULL) {
					if (l != NULL)
						add_to_tree_from_branch_min(t, r);
					if (el->right != NULL)
						el->right->right = r;
					else
						el->right = r;
				}

				if (l != NULL) {
					if (el->right != NULL)
						el->right->left = l;
					else
						el->right = l;
				}


				t->size--;
			}
		}
	}
}

void print_node(node* node, int depth) {
	if (node == NULL) {
		return;
	}
	print_node(node->right, depth + 1);
	printf("\n");
	for (int i = 0; i < depth; i++) {
		printf("\t");
	}
	printf("%d", node->value);
	print_node(node->left, depth + 1);
}

void print_tree(tree* tree) {
	print_node(tree->root, 0);
	return;
}
