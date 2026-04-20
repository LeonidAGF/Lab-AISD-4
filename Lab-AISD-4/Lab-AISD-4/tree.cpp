#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void search(tree* t, char * key) {
	node* p = t->root;
	while (p != NULL && p->key != key) {
		if (strcmp(key, p->key)<0)
			p = p->left;
		else
			p = p->right;
	}
	if(p!=NULL && p->key==key)
		printf("%s %lf", p->key,p->value);
	else
		printf("not found");
}

void rotate_left(node* n) {
	if (n == NULL || n->right == NULL)
		return;
	node* p = n->right;

	p->parent = n->parent;
	if (n->parent != NULL) {
		if (n->parent->left == n)
			n->parent->left = p;
		else
			n->parent->right = p;
	}

	n->right = p->left;
	if (p->left != NULL)
		p->left->parent = n;

	n->parent = p;
	p->left = n;
}

void rotate_right(node* n) {
	if (n == NULL || n->left == NULL)
		return;
	node* p = n->left;

	p->parent = n->parent;
	if (n->parent != NULL) {
		if (n->parent->left == n)
			n->parent->left = p;
		else
			n->parent->right = p;
	}

	n->left = p->right;
	if (p->right != NULL)
		p->right->parent = n;

	n->parent = p;
	p->right = n;
}

void fixInsertion(node* tree,bool is_root) {
	if (is_root) {
		tree->color = 2;
		return;
	}
	while (tree->parent != NULL && tree->parent->color == 1) {
		if (tree->parent->left == tree) {
			if (tree->parent->parent != NULL && ((tree->parent->parent->left != NULL && tree->parent->parent->left != tree->parent && tree->parent->parent->left->color == 1) || (tree->parent->parent->right != NULL && tree->parent->parent->right != tree->parent && tree->parent->parent->right->color == 1))) {
				//красный дядя
				tree->parent->parent->color = 1;
				if (tree->parent->parent->left != NULL && tree->parent->parent->left != tree->parent)
					tree->parent->parent->left->color = 2;
				else
					tree->parent->parent->right->color = 2;
				tree->parent->color = 2;
				tree = tree->parent->parent;
			}
			else {
				if (tree->parent->right == tree) {
					tree = tree->parent;
					rotate_left(tree);
				}
				tree->parent->color = 2;
				if (tree->parent->parent != NULL) {
					tree->parent->parent->color = 1;
					rotate_right(tree->parent->parent);
				}
			}
		}
		else {
			if (tree->parent->parent != NULL && ((tree->parent->parent->left != NULL && tree->parent->parent->left != tree->parent && tree->parent->parent->left->color == 1) || (tree->parent->parent->right != NULL && tree->parent->parent->right != tree->parent && tree->parent->parent->right->color == 1))) {
				//красный дядя
				tree->parent->parent->color = 1;
				if (tree->parent->parent->left != NULL && tree->parent->parent->left != tree->parent)
					tree->parent->parent->left->color = 2;
				else
					tree->parent->parent->right->color = 2;
				tree->parent->color = 2;
				tree = tree->parent->parent;
			}
			else {
				if (tree->parent->left == tree) {
					tree = tree->parent;
					rotate_right(tree);
				}
				tree->parent->color = 2;
				if (tree->parent->parent != NULL) {
					tree->parent->parent->color = 1;
					rotate_left(tree->parent->parent);
				}
			}
		}
	}
	node* root = tree;
	while (root->parent != NULL)
		root = root->parent;
	root->color = 2;
}


void insert(tree* tree, char* key, double value) {

	node* t = (node*)malloc(sizeof(node));
	t->color = 1;//red
	t->key = key;
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	bool is_root = 1;

	if (tree->root == NULL) {
		tree->root = t;
		tree->root->parent = NULL;
	}
	else {
		node* p = tree->root;
		node* q = NULL;

		while(p != NULL){
			q = p;
			if (strcmp(p->key, t->key)<0)
				p = p->right;
			else
				p = p->left;
		}
		t->parent = q;
		if (strcmp(q->key, t->key) < 0)
			q->right = t;
		else
			q->left = t;
		is_root = 0;
	}
	fixInsertion(t, is_root);
	while (tree->root->parent != NULL) {
		tree->root = tree->root->parent;
	}
}

void add_el(tree* t, char* key, double value) {
	if (t->root == NULL) {
		t->size++;
		node* n = (node*)malloc(sizeof(node));
		if (n != NULL) {
			n->key = key;
			n->value = value;
			n->left = NULL;
			n->right = NULL;
			n->color = 2;
			n->parent = NULL;
			t->root = n;
		}
		return;
	}
	else {
		t->size++;
		insert(t, key, value);
	}
}

void fixDeleting(tree* t, node* p, node* p_parent) {
	while (p != t->root && (p == NULL || p->color == 2)) {
		if (p == p_parent->left) {
			node* b = p_parent->right;

			if (b == NULL)
				break;

			//Красный брат
			if (b != NULL && b->color == 1) {
				b->color = 2;
				p_parent->color = 1;
				rotate_left(p_parent);
				if (t->root == p_parent)
					t->root = b;
				b = p_parent->right;
			}

			if ((b->left == NULL || b->left->color == 2) && (b->right == NULL || b->right->color == 2)) {
				b->color = 1;
				p = p_parent;
				p_parent = p->parent;
			}
			else {
				if (b->right == NULL || b->right->color == 2) {
					if (b->left != NULL)
						b->left->color = 2;
					b->color = 1;
					rotate_right(b);
					b = p_parent->right;
				}
				b->color = p_parent->color;
				p_parent->color = 2;
				if (b->right != NULL)
					b->right->color = 2;
				rotate_left(p_parent);
				if (t->root == p_parent) t->root = b;
				p = t->root;
			}
		}
		else {
			//p — правый ребенок
			node* b = p_parent->left;

			if (b != NULL && b->color == 1) {
				b->color = 2;
				p_parent->color = 1;
				rotate_right(p_parent);
				if (t->root == p_parent)
					t->root = b;
				b = p_parent->left;
			}

			if ((b->left == NULL || b->left->color == 2) && (b->right == NULL || b->right->color == 2)) {
				b->color = 1;
				p = p_parent;
				p_parent = p->parent;
			}
			else {
				if (b->left == NULL || b->left->color == 2) {
					if (b->right != NULL)
						b->right->color = 2;
					b->color = 1;
					rotate_left(b);
					b = p_parent->left;
				}
				b->color = p_parent->color;
				p_parent->color = 2;
				if (b->left != NULL)
					b->left->color = 2;
				rotate_right(p_parent);
				if (t->root == p_parent) 
					t->root = b;
				p = t->root;
			}
		}
	}
	if (p != NULL)
		p->color = 2;
	if (t->root != NULL)
		t->root->color = 2;
}

void delete_value(tree* t, char* key) {
	node* p = t->root;
	node* y = NULL;
	node* q = NULL;

	while (p != NULL && p->key != key) {
		if (strcmp(key, p->key) < 0)
			p = p->left;
		else
			p = p->right;
	}

	if (p == NULL) 
		return;

	if (p->left == NULL || p->right == NULL) {
		y = p;
	}
	else {
		node* pr = p->right;
		while (pr->left != NULL)
			pr = pr->left;
		y = pr;
	}

	if (y->left != NULL) {
		q = y->left;
	}
	else {
		q = y->right;
	}

	if (q != NULL) {
		q->parent = y->parent;
	}

	if (y->parent == NULL) {
		t->root = q;
	}
	else {
		if (y == y->parent->left) {
			y->parent->left = q;
		}
		else {
			y->parent->right = q;
		}
	}

	if (y != p) {
		p->key = y->key;
	}
	if (y->color == 2) {
		fixDeleting(t,q,y->parent);
	}

	if (t->root != NULL && t->root->parent != NULL) {
		while (t->root->parent != NULL)
			t->root = t->root->parent;
	}

	free(y);
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
	if(node->color==1)
		printf("[%s %lf]", node->key, node->value);
	else
		printf("(%s %lf)", node->key, node->value);
	print_node(node->left, depth + 1);
}

void print_tree(tree* tree) {
	print_node(tree->root, 0);
	return;
}
