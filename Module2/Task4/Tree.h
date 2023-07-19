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

Node* create(); // ���� �������� ������

Node* insert(Node* node, int value); // ������� ����
Node* delete(Node* node, int value); // �������� ����
Node* minimum(Node* node); // ����� ������������ ����
int print(Node* node, int wide, int x, int y, int type); // ������� ������ �� �����
void clear(Node* node); // �������� ������