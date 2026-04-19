#pragma once
typedef struct node {
	int value;
	int depth;
	int color; //1 - red, 2 - black
	node* left;
	node* right;
} node;

typedef struct {
	int size;
	node* root;
}tree;

void add(node* tree, int value);

void add_el(tree* t, int value);

void print(tree* tree);

void add_to_tree_from_branch_min(tree* t, node* el);

void delete_value(tree* t, int value);

void print_node(node* node, int depth);

void print_tree(tree* tree);