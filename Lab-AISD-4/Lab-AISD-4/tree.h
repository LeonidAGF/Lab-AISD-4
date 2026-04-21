#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int color; //1 - red, 2 - black
	double value;
	char * key;
	node* parent;
	node* left;
	node* right;
} node;

typedef struct {
	int size;
	node* root;
}tree;

void search(tree* t, char * key, FILE* stream);

void rotate_left(node* tree);

void rotate_right(node* tree);

void insert(tree* tree, char * key, double value);

void fixInsertion(node* tree, bool is_root);

void add_el(tree* t, char * key, double value);

void fixDeleting(tree* t, node* p, node* p_parent);

void delete_value(tree* t, char * key);

void print_node(node* node, int depth, FILE* stream);

void print_tree(tree* tree, FILE* stream);