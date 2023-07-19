#include "Tree.h"

Node* create() {
	Node* root = NULL;
	puts("\n������� ���-�� ��������� � ������:");
	int size = 0;
	while (size <= 0) {
		scanf_s("%d", &size);
		getchar();
	}

	puts("\n1. ��������� ��������");
	puts("2. ��������� �������");
	puts("3. ��������� � ����");

	int choice;
	scanf_s("%d", &choice);
	getchar();

	switch (choice) {
	case 1: {
		int item;
		for (int i = 0; i < size; i++) {
			item = rand() % 100;
			root = insert(root, item);
		}
		break;
	}
	case 2:
		puts("������� �������� ������:\n");
		int item;
		for (int i = 0; i < size; i++) {
			scanf_s("%d", &item);
			getchar();
			root = insert(root, item);
		}
		break;
	case 3:
		menu();
		break;
	default:
		puts("������� �������� ��������. ������� � �������� ����.\n");
		menu();
		break;
	}

	return root;
}

Node* minimum(Node* node) { // ���������� � ����� ����� ���� (���. ��������)
	if (!node->left) return node;
	return minimum(node->left);
}

Node* delete(Node* node, int value) {

	if (!node) // ���� ���� �����������, �� ������� �����
		return node;

	if (value < node->value)  // ����� ���� �����
		node->left = delete(node->left, value);

	else if (value > node->value) // ����� ���� ������
		node->right = delete(node->right, value);

	else if (node->left && node->right) { // ���� � ���������� ���� ���� ��� �������, �� ����� ����������� ������
		node->value = minimum(node->right)->value; // ������� ����������� �������� � ������� ������� � ������ ��� � ��������� ���� (���� ������)
		node->right = delete(node->right, node->value); // ���������� ������ � ���������� �������� ������ ��� ������������� ��������
	}
	else { // ��������� ���� ������
		//Node* tmp = node;
		if (node->left) {// �������� ��� ���������� ��������
			Node* left = node->left;
			//Node* parent = node->parent;
			left->parent = node->parent;
			free(node);
			node = NULL;
			return left;
			//parent->left = left;
			//node = node->left;
		}
		else if (node->right) {// ���� ��� ������, �� ���������� ��������
			Node* right = node->right;
			//Node* parent = node->parent;
			right->parent = node->parent;
			free(node);
			node = NULL;
			return right;
			//parent->right = right;
			//node = node->right;
		}
		else { // ���� ���� - ������ �������
			free(node);
			node = NULL;
		}
		//free(tmp);
		//tmp = NULL;
	}
	return node;
}

Node* insert(Node* node, int value) { // ������� ��������� �������� � ������
	if (!node) { // ������ ������ ����
		node = (Node*)malloc(sizeof(Node));
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		return node;
	}
	else { // ����� �� ������ ����
		if (value < node->value) { // �����
			node->left = insert(node->left, value);
			Node* left = node->left;
			left->parent = node;
		}
		else if (value > node->value) { // ������
			node->right = insert(node->right, value);
			Node* right = node->right;
			right->parent = node;
		}
	} // ���� ����� ���� ��� ����������, �� ���������� ��� ��
	return node;
}

int print(Node* node, int wide, int x, int y, int type) {// type = 0 - ������, c = 1 - �����, c = 2 - ������
	if (node) {
		switch (type) { // ��� ����� ������� ����� ����� ��� ������
		case 1:
			x -= wide;
			break;
		case 2:
			x += wide;
			break;
		}

		setConsoleCoords(x, y++);
		if (type == 1) printf("      /");
		if (type == 2) printf(" \\");

		setConsoleCoords(x, y++);
		printf("%5d", node->value);

		if (wide > 5) // ��������� ������ ����� ��������� ������ �� ����� ������ �������
			wide -= 8;

		int l = print(node->left, wide, x, y, 1);
		int r = print(node->right, wide, x, y, 2);
		if (l > r) return l; // ����� ����� ������ ����� ��� ������ ������
		else return r;
	}
	else
		return y; // ������� ������� ��������� �� Y
}

void clear(Node* node) {
	if (node) {
		clear(node->left);
		clear(node->right);
		free(node);
		node = NULL;
	}
}