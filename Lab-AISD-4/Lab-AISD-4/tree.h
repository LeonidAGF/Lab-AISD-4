#pragma once
typedef struct node {
	int value;
	int color; //1 - red, 2 - black
	node* parent;
	node* left;
	node* right;
} node;

typedef struct {
	int size;
	node* root;
}tree;

void search(tree* t, int value);

void rotate_left(node* tree);

void rotate_right(node* tree);

void insert(tree* tree, int value);

void fixInsertion(node* tree, bool is_root);

void add_el(tree* t, int value);

void fixDeleting(tree* t, node* p, node* p_parent);

void delete_value(tree* t, int value);

void print_node(node* node, int depth);

void print_tree(tree* tree);