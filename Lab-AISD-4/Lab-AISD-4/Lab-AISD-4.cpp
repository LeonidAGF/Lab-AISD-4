#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tests.h"

int main() {
	int i1 = test1();
	int i2 = test2();
	int i3 = test3();
	int i4 = test4();
	int i5 = test5();

	if (i1)
		printf("error in test1\n");
	if (i2)
		printf("error in test2\n");
	if (i3)
		printf("error in test3\n");
	if (i4)
		printf("error in test4\n");
	if (i5)
		printf("error in test5\n");

	tree tree = { 0,NULL };
	int input_com;
	double input_value;

	printf("choose mode: from file - 1, from console - 2\n");
	scanf_s("%d", &input_com);

	if (input_com == 1) {
		printf("file name:\n");

		char* name = (char*)malloc(sizeof(char) * 100);
		scanf_s("%100s", name, 101);


		const int BUFFER_SIZE = 100;
		FILE* file = NULL;
		fopen_s(&file, name, "r");
		char buffer[BUFFER_SIZE];
		int pos_data = 0;
		int drob = 0;
		double m = 0.1;
		while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
			char* str = (char*)malloc(sizeof(char) * 7);
			double input_value = 0;
			int str_pos = 0;
			switch (buffer[pos_data]) {
			case '1':
				
				pos_data += 2;

				while (buffer[pos_data] != ' ' && str_pos<6) {
					str[str_pos] = buffer[pos_data];
					str_pos++;
					pos_data++;
				}
				pos_data++;

				while (buffer[pos_data] != ' ' && buffer[pos_data] != '\0') {
					if (buffer[pos_data] != '.') {
						drob = 1;
						pos_data++;
					}
					if (drob) {
						input_value += (buffer[pos_data] - 48)*m;
						m *= 0.1;
					}
					else{
						input_value *= 10;
						input_value += (buffer[pos_data] - 48);
					}
					pos_data++;
				}

				str[str_pos] = '\0';
				add_el(&tree, str, input_value);
				break;
			case '2':
				pos_data += 2;

				while (buffer[pos_data] != ' ' && str_pos < 6) {
					str[str_pos] = buffer[pos_data];
					str_pos++;
					pos_data++;
				}
				delete_value(&tree, str);
				break;
			case '3':
				print_tree(&tree);
				printf("\n");
				break;
			case '4':
				pos_data += 2;

				while (buffer[pos_data] != ' ' && str_pos < 6) {
					str[str_pos] = buffer[pos_data];
					str_pos++;
					pos_data++;
				}
				search(&tree, str);
				printf("\n");
				break;
			case '5':
				while (tree.root != NULL)
					delete_value(&tree, tree.root->key);
				return 0;
			default:
				break;
			}

			pos_data = 0;
		}
		fclose(file);
	}
	else {
		while (1) {
			char* str = (char*)malloc(sizeof(char) * 6);
			printf("add - 1, delete - 2, print tree - 3, search by key - 4 , exit - 5\n");
			scanf_s("%d", &input_com);
			getchar();
			switch (input_com) {
			case 1:
				scanf_s("%6s", str, 7);
				scanf_s("%lf", &input_value);
				add_el(&tree, str, input_value);
				break;
			case 2:
				scanf_s("%6s", str, 7);
				delete_value(&tree, str);
				break;
			case 3:
				print_tree(&tree);
				printf("\n");
				break;
			case 4:
				scanf_s("%6s", str, 7);
				search(&tree, str);
				printf("\n");
				break;
			case 5:
				while (tree.root != NULL)
					delete_value(&tree, tree.root->key);
				return 0;
			default:
				break;
			}
		}
	}
	return 0;
}