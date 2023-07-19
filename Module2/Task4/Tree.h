#pragma once

#include <stdio.h>
#include <malloc.h>

#include "Console.h"

#define NULL 0;

typedef struct Node {
	int value;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Node;

Node* create(); // меню создание дерева

Node* insert(Node* node, int value); // вставка узла
Node* delete(Node* node, int value); // удаление узла
Node* minimum(Node* node); // поиск минимального узла
int print(Node* node, int wide, int x, int y, int type); // вывести дерево на экран
void clear(Node* node); // очистить дерево