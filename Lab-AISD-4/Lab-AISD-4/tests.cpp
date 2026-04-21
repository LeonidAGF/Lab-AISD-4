#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test1() {
	//тест на выполнение базовых операций
	tree tree = { 0,NULL };
	
	char* s1 = (char*)malloc(sizeof(char) * 7);
	char* s2 = (char*)malloc(sizeof(char) * 7);
	char* s3 = (char*)malloc(sizeof(char) * 7);
	char* s4 = (char*)malloc(sizeof(char) * 7);
	char* s5 = (char*)malloc(sizeof(char) * 7);
	char* s6 = (char*)malloc(sizeof(char) * 7);
	char* s7 = (char*)malloc(sizeof(char) * 7);
	char* s8 = (char*)malloc(sizeof(char) * 7);
	char* s9 = (char*)malloc(sizeof(char) * 7);
	char* s10 = (char*)malloc(sizeof(char) * 7);
	char* s11 = (char*)malloc(sizeof(char) * 7);
	char* s12 = (char*)malloc(sizeof(char) * 7);
	char* s13 = (char*)malloc(sizeof(char) * 7);
	char* s14 = (char*)malloc(sizeof(char) * 7);
	char* s15 = (char*)malloc(sizeof(char) * 7);
	char* s16 = (char*)malloc(sizeof(char) * 7);
	char* s17 = (char*)malloc(sizeof(char) * 7);
	char* s18 = (char*)malloc(sizeof(char) * 7);
	char* s19 = (char*)malloc(sizeof(char) * 7);
	char* s20 = (char*)malloc(sizeof(char) * 7);
	char* s21 = (char*)malloc(sizeof(char) * 7);

	strcpy_s(s1, sizeof(char) * 7, "123456");
	strcpy_s(s2, sizeof(char) * 7, "234567");
	strcpy_s(s3, sizeof(char) * 7, "345678");
	strcpy_s(s4, sizeof(char) * 7, "456789");
	strcpy_s(s5, sizeof(char) * 7, "112345");
	strcpy_s(s6, sizeof(char) * 7, "223456");
	strcpy_s(s21, sizeof(char) * 7, "423456");
	strcpy_s(s7, sizeof(char) * 7, "263456");
	strcpy_s(s8, sizeof(char) * 7, "227456");
	strcpy_s(s9, sizeof(char) * 7, "243456");
	strcpy_s(s10, sizeof(char) * 7, "223336");
	strcpy_s(s11, sizeof(char) * 7, "323356");
	strcpy_s(s12, sizeof(char) * 7, "223666");
	strcpy_s(s13, sizeof(char) * 7, "666456");
	strcpy_s(s14, sizeof(char) * 7, "226056");
	strcpy_s(s15, sizeof(char) * 7, "000000");
	strcpy_s(s16, sizeof(char) * 7, "220045");
	strcpy_s(s17, sizeof(char) * 7, "203406");
	strcpy_s(s18, sizeof(char) * 7, "003006");
	strcpy_s(s19, sizeof(char) * 7, "533456");
	strcpy_s(s20, sizeof(char) * 7, "aaabbb");

	add_el(&tree, s1,1.0);
	add_el(&tree, s2,60.1);
	add_el(&tree, s3,6.0);
	add_el(&tree, s4,6.0);
	add_el(&tree, s5,6.35);
	add_el(&tree, s6,60000.0);
	add_el(&tree, s7,600.0);
	add_el(&tree, s8,60000.6);
	add_el(&tree, s9,99999.0);
	add_el(&tree, s10,0.0);
	add_el(&tree, s11,60.355);
	add_el(&tree, s12,0.35);
	add_el(&tree, s13,600.0);
	add_el(&tree, s14,60000.0);
	add_el(&tree, s15,60000.0);
	add_el(&tree, s16,60000.0);
	add_el(&tree, s17,60000.0);
	add_el(&tree, s18,60000.0);
	add_el(&tree, s19,60000.0);
	add_el(&tree, s20,60000.0);
	add_el(&tree, s21,60000.0);

	delete_value(&tree, s5);
	delete_value(&tree, s1);
	
	search(&tree, s2,stdout);
	print_tree(&tree,stdout);

	while (tree.root != NULL)
		delete_value(&tree, tree.root->key);

	system("cls");//для очистки консоли
	
	return 0;
}

int test2() {
	//тест на левый поворот
	tree tree = { 0,NULL };
	int res = 0;

	char* s1 = (char*)malloc(sizeof(char) * 7);
	char* s2 = (char*)malloc(sizeof(char) * 7);
	char* s3 = (char*)malloc(sizeof(char) * 7);

	strcpy_s(s1, sizeof(char) * 7, "1     ");
	strcpy_s(s2, sizeof(char) * 7, "2     ");
	strcpy_s(s3, sizeof(char) * 7, "3     ");

	add_el(&tree, s1, 1.0);
	add_el(&tree, s2, 60.1);
	add_el(&tree, s3, 120.0);

	if (tree.root->key != s2)
		res = 1;

	while (tree.root != NULL)
		delete_value(&tree, tree.root->key);

	system("cls");//для очистки консоли
	return res;
}

int test3() {
	//тест на правый поворот
	tree tree = { 0,NULL };
	int res = 0;

	char* s1 = (char*)malloc(sizeof(char) * 7);
	char* s2 = (char*)malloc(sizeof(char) * 7);
	char* s3 = (char*)malloc(sizeof(char) * 7);

	strcpy_s(s1, sizeof(char) * 7, "1     ");
	strcpy_s(s2, sizeof(char) * 7, "2     ");
	strcpy_s(s3, sizeof(char) * 7, "3     ");

	add_el(&tree, s3, 1.0);
	add_el(&tree, s2, 60.1);
	add_el(&tree, s2, 120.0);

	if (tree.root->key != s2)
		res = 1;

	while (tree.root != NULL)
		delete_value(&tree, tree.root->key);

	system("cls");//для очистки консоли
	return res;
}

int test4() {
	//красный дядя
	tree tree = { 0,NULL };
	int res = 1;

	char* s1 = (char*)malloc(sizeof(char) * 7);
	char* s2 = (char*)malloc(sizeof(char) * 7);
	char* s3 = (char*)malloc(sizeof(char) * 7);
	char* s4 = (char*)malloc(sizeof(char) * 7);

	strcpy_s(s1, sizeof(char) * 7, "20    ");
	strcpy_s(s2, sizeof(char) * 7, "30    ");
	strcpy_s(s3, sizeof(char) * 7, "10    ");
	strcpy_s(s4, sizeof(char) * 7, "0     ");

	add_el(&tree, s1, 1.0);
	add_el(&tree, s2, 60.1);
	add_el(&tree, s3, 6.0);
	add_el(&tree, s4, 6.0);

	if (tree.root->right->color == 2 && tree.root->left->color == 2)
		res = 0;

	while (tree.root != NULL)
		delete_value(&tree, tree.root->key);

	system("cls");//для очистки консоли
	return res;
}

int test5() {
	tree tree = { 0,NULL };
	int res = 1;

	char* s1 = (char*)malloc(sizeof(char) * 7);
	char* s2 = (char*)malloc(sizeof(char) * 7);
	char* s3 = (char*)malloc(sizeof(char) * 7);
	char* s4 = (char*)malloc(sizeof(char) * 7);

	strcpy_s(s1, sizeof(char) * 7, "10    ");
	strcpy_s(s2, sizeof(char) * 7, "0     ");
	strcpy_s(s3, sizeof(char) * 7, "15    ");
	strcpy_s(s4, sizeof(char) * 7, "12    ");

	add_el(&tree, s1, 1.0);
	add_el(&tree, s2, 60.1);
	add_el(&tree, s3, 6.0);
	add_el(&tree, s4, 6.0);

	delete_value(&tree, s2);

	if (tree.root->key == s4 && tree.root->left->color == 2 && tree.root->right->color == 2)
		res = 0;

	while (tree.root != NULL)
		delete_value(&tree, tree.root->key);

	system("cls");//для очистки консоли
	return res;
}