// Односвязный список с int
// Есть возможность нахождения разности, объединения и пересечения двух списков

#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>

#include "List.h"

void menu(); // основное меню

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
    menu();
}

void menu()
{
    Node* list = NULL;

    int choice = -1;
    while (1) {
        system("clear");
        puts("Введите цифру для выбора одного из пуктов меню:");
        puts("1. Создать список с N случайных элементов");
        puts("2. Напечатать список");
        puts("3. Добавить элемент в список");
        puts("4. Редактировать элемент списка");
        puts("5. Удалить элемент списка");
        puts("6. Очистить список");
        puts("7. Задание. Создать 2 списка заданных размерностей. Получить их объединение, пересечение и разность");
        puts("0. Выход");

        scanf_s("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1: { // рандомный список с N элементами
            system("clear");
            clear(&list);
            puts("Введите размер нового списка: ");
            int size = 0;
            while (size < 1) {
                scanf_s("%d", &size);
                getchar();
            }
            list = create(size);
            puts("\nСписок создан!\n");
            _getch();
            break;
        }
        case 2: // печать
            system("clear");
            if (!getSize(list))
                puts("Список пуст!\n");
            else {
                puts("Выберите вариант вывода списка:");
                puts("1. Обычный (от головы к концу)");
                puts("2. В обратном порядке (от конца к голове)");

                int type;
                scanf_s("%d", &type);
                getchar();
                switch (type)
                {
                case 1:
                    puts("\nСписок:");
                    print(list);
                    puts("\n");
                    break;
                case 2:
                    puts("\nСписок в обратном порядке:");
                    printBack(list);
                    puts("\n");
                    break;
                default:
                    puts("\nВведено некорректное значение. Возврат к основному меню.\n");
                    break;
                }
            }
            _getch();
            break;
        case 3: // добавить
            system("clear");
            if (!getSize(list)) {
                puts("Список пуст! Новый элемент будет являться головой.\n");
                puts("Введите значение нового элемента (если будет введено значение, отличное от целого числа, будет записан 0): ");
                int value = 0;
                scanf_s("%d", &value);
                getchar();
                init(&list, value);
                puts("\nПервый элемент списка добавлен!\n");
            }
            else {
                puts("Выберите местоположение нового элемента списка:");
                puts("1. В начало");
                puts("2. В конец");
                puts("3. Свой вариант");

                int type;
                scanf_s("%d", &type);
                getchar();

                puts("\nВведите значение нового элемента (если будет введено значение, отличное от целого числа, будет записан 0): ");
                int value = 0;
                scanf_s("%d", &value);
                getchar();

                switch (type)
                {
                case 1:
                    addFirst(&list, value);
                    puts("\nПервый элемент списка добавлен!\n");
                    break;
                case 2:
                    addLast(&list, value);
                    puts("\nПоследний элемент списка добавлен!\n");
                    break;
                case 3:
                    puts("\nВведите позицию нового элемента (начиная с 0, элемент будет вставлен ПОСЛЕ выбранного): ");
                    int pos = -1;
                    while (pos < 0) {
                        scanf_s("%d", &pos);
                        getchar();
                    }
                    addPosition(&list, value, pos);
                    puts("\nНовый элемент списка добавлен!\n");
                    break;
                default:
                    puts("\nВведено некорректное значение. Возврат к основному меню.\n");
                    break;
                }
            }
            _getch();
            break;
        case 4: // редактировать
            system("clear");
            if (!getSize(list))
                puts("Список пуст!\n");
            else {
                puts("Выберите местоположение изменяемого элемента списка:");
                puts("1. Первый");
                puts("2. Последний");
                puts("3. Свой вариант");

                int type;
                scanf_s("%d", &type);
                getchar();

                puts("\nВведите новое значение изменяемого элемента (если будет введено значение, отличное от целого числа, будет записан 0): ");
                int value = 0;
                scanf_s("%d", &value);
                getchar();

                switch (type)
                {
                case 1:
                    editFirst(&list, value);
                    puts("\nПервый элемент списка изменен!\n");
                    break;
                case 2:
                    editLast(&list, value);
                    puts("\nПоследний элемент списка изменен!\n");
                    break;
                case 3:
                    puts("\nВведите позицию изменяемого элемента (начиная с 0): ");
                    int pos = -1;
                    while (pos < 0) {
                        scanf_s("%d", &pos);
                        getchar();
                    }
                    editPosition(&list, value, pos);
                    puts("\nЭлемент списка изменен!\n");
                    break;
                default:
                    puts("\nВведено некорректное значение. Возврат к основному меню.\n");
                    break;
                }
            }
            _getch();
            break;
        case 5: // удалить
            system("clear");
            if (!getSize(list))
                puts("Список пуст!\n");
            else {
                puts("Выберите местоположение удаляемого элемента списка:");
                puts("1. Первый");
                puts("2. Последний");
                puts("3. Свой вариант");

                int type;
                scanf_s("%d", &type);
                getchar();

                switch (type)
                {
                case 1:
                    delFirst(&list);
                    puts("\nПервый элемент списка удален!\n");
                    break;
                case 2:
                    delLast(&list);
                    puts("\nПоследний элемент списка удален!\n");
                    break;
                case 3:
                    puts("\nВведите позицию удаляемого элемента (начиная с 0): ");
                    int pos = -1;
                    while (pos < 0) {
                        scanf_s("%d", &pos);
                        getchar();
                    }
                    delPosition(&list, pos);
                    puts("\nЭлемент списка удален!\n");
                    break;
                default:
                    puts("\nВведено некорректное значение. Возврат к основному меню.\n");
                    break;
                }
            }
            _getch();
            break;
        case 6: // очистить
            system("clear");
            if (!getSize(list))
                puts("Список пуст!\n");
            else {
                clear(&list);
                puts("Список очищен!\n");
            }
            _getch();
            break;
        case 7: // задание: объединение, разность, пересечение
            system("clear");
            puts("Для выполнения задания автоматически создаются 2 списка, из которых в дальнейшем можно получить объединение, разность и пересечение.");

            puts("\nВведите размерность 1 списка: ");
            int size1 = -1;
            while (size1 < 0) {
                scanf_s("%d", &size1);
                getchar();
            }

            puts("\nВведите размерность 2 списка: ");
            int size2 = -1;
            while (size2 < 0) {
                scanf_s("%d", &size2);
                getchar();
            }

            Node* list1 = create(size1);
            Node* list2 = create(size2);

            puts("\nСписок 1:");
            print(list1);
            puts("\nСписок 2:");
            print(list2);

            puts("\nПеречение:");
            print(intersection(list1, list2));

            puts("\nОбъединение:");
            print(merge(list1, list2));

            puts("\nРазность:");
            print(difference(list1, list2));
            puts("\n");

            clear(&list1);
            clear(&list2);

            _getch();
            break;
        case 0:
            clear(&list);
            exit(0);
        default:
            menu();
        }
    }
}