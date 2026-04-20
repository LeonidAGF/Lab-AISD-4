#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
	tree tree = { 0,NULL };
	int input_com, input_value;
	while (1) {
		printf("add - 1, delete - 2, print tree - 3, search by key - 4 , exit - 5\n");
		scanf_s("%d", &input_com);
		switch (input_com) {
		case 1:
			scanf_s("%d", &input_value);
			add_el(&tree, input_value);
			break;
		case 2:
			scanf_s("%d", &input_value);
			delete_value(&tree, input_value);
			break;
		case 3:
			print_tree(&tree);
			printf("\n");
			break;
		case 4:
			scanf_s("%d", &input_value);
			search(&tree,input_value);
			printf("\n");
			break;
		case 5:
			while (tree.root != NULL)
				delete_value(&tree, tree.root->value);
			return 0;
		default:
			break;
		}
	}
	return 0;
}