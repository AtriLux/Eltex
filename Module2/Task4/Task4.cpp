// Бинарное дерево поиска с типом int. Алгоритмы работают по рекурсии

#include <locale.h>
#include <stdlib.h>
#include <time.h>

#include "Tree.h"
#include "Console.h"

void menu(); // основное меню

int main() {

	srand(time(0));
	setlocale(LC_ALL, "Rus");
	menu();
}

void menu() {

	Node* tree = NULL;
	while (1) {
		puts("\nВведите цифру для выбора одного из пуктов меню:");
		puts("1. Создать дерево");
		puts("2. Добавить узел (если дерево не существует, оно будет автоматически создано)");
		puts("3. Вывести дерево на экран");
		puts("4. Удалить узел");
		puts("5. Очистить дерево");
		puts("0. Выход");

		int choice;
		scanf_s("%d", &choice);
		getchar();

		switch (choice) {
		case 1: {
			tree = create();
			break;
		}
		case 2:
			puts("\nВведите значение добавляемого узла дерева:");
			int item = 0;
			scanf_s("%d", &item);
			getchar();
			tree = insert(tree, item);
			puts("\nОперация произведена.");
			break;
		case 3: {
			int y = print(tree, 29, getConsoleSizeX() / 2 - 5, getConsoleCoordY() - 1, 0);
			setConsoleCoords(0, y+2);
			puts("\nВывод окончен");
			break;
		}
		case 4: {
			puts("\nВведите значение удаляемого узла дерева:");
			int item = 0;
			scanf_s("%d", &item);
			getchar();
			tree = delete(tree, item);
			puts("\nОперация произведена.");
			break;
		}
		case 5:
			clear(tree);
			tree = NULL;
			break;
		case 0:
			clear(tree);
			exit(0);
			break;
		default:
			puts("Введено неверное значение. Попробуйте еще раз.\n");
			menu();
			break;
		}
	}
}