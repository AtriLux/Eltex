#include "Tree.h"

Node* create() {
	Node* root = NULL;
	puts("\nВведите кол-во элементов в дереве:");
	int size = 0;
	while (size <= 0) {
		scanf_s("%d", &size);
		getchar();
	}

	puts("\n1. Заполнить рандомно");
	puts("2. Заполнить вручную");
	puts("3. Вернуться в меню");

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
		puts("Введите элементы дерева:\n");
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
		puts("Введено неверное значение. Возврат в основное меню.\n");
		menu();
		break;
	}

	return root;
}

Node* minimum(Node* node) { // опускаемся в самый левый лист (мин. значение)
	if (!node->left) return node;
	return minimum(node->left);
}

Node* delete(Node* node, int value) {

	if (!node) // если узлы закончились, то возврат назад
		return node;

	if (value < node->value)  // поиск узла влево
		node->left = delete(node->left, value);

	else if (value > node->value) // поиск узла вправо
		node->right = delete(node->right, value);

	else if (node->left && node->right) { // если у удаляемого узла есть оба ребенка, то нужно перестроить дерево
		node->value = minimum(node->right)->value; // находим минимальное значение у правого ребенка и ставим его в удаляемый узел (типа замена)
		node->right = delete(node->right, node->value); // спускаемся вправо и продолжаем удаление только что перенесенного значения
	}
	else { // удаляемый узел найден
		//Node* tmp = node;
		if (node->left) {// заменяем его наименьшим ребенком
			Node* left = node->left;
			//Node* parent = node->parent;
			left->parent = node->parent;
			free(node);
			node = NULL;
			return left;
			//parent->left = left;
			//node = node->left;
		}
		else if (node->right) {// если нет левого, то наибольшим ребенком
			Node* right = node->right;
			//Node* parent = node->parent;
			right->parent = node->parent;
			free(node);
			node = NULL;
			return right;
			//parent->right = right;
			//node = node->right;
		}
		else { // если лист - просто удаляем
			free(node);
			node = NULL;
		}
		//free(tmp);
		//tmp = NULL;
	}
	return node;
}

Node* insert(Node* node, int value) { // вставка заданного элемента в дерево
	if (!node) { // найден пустой узел
		node = (Node*)malloc(sizeof(Node));
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		return node;
	}
	else { // спуск по дереву вниз
		if (value < node->value) { // влево
			node->left = insert(node->left, value);
			Node* left = node->left;
			left->parent = node;
		}
		else if (value > node->value) { // вправо
			node->right = insert(node->right, value);
			Node* right = node->right;
			right->parent = node;
		}
	} // если такой узел уже существует, то возвращать его же
	return node;
}

int print(Node* node, int wide, int x, int y, int type) {// type = 0 - корень, c = 1 - левый, c = 2 - правый
	if (node) {
		switch (type) { // для детей смещать вывод влево или вправо
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

		if (wide > 5) // уменьшить ширину между соседними детьми на более низкиз уровнях
			wide -= 8;

		int l = print(node->left, wide, x, y, 1);
		int r = print(node->right, wide, x, y, 2);
		if (l > r) return l; // поиск самой нижней точки при выводе дерева
		else return r;
	}
	else
		return y; // возврат текуего положения по Y
}

void clear(Node* node) {
	if (node) {
		clear(node->left);
		clear(node->right);
		free(node);
		node = NULL;
	}
}