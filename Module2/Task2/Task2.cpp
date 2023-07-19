#include <locale.h>
#include <stdio.h>
#include <malloc.h>

int abc[3], R; // input data
int n1, n2; // count for solve
int **res1, **res2; // arrays for solve as [ [1 емкость], [2 ем.], [3 ем.]; [] [] []; ... ]

int var1(); // solve type 1
int var2(); // solve type 2
void resolve(); // repeat all function
int menu(); // text and choice
void inputData(); // input a, b, c, r
void sort(); // sort abs[3] as [max, middle, min]
void printRes(int** res, int size); // attractive output
int checkRes(int* res); // check current state for win (like-a-bool xD)
void clear(int** res, int size); // free array


int main()
{
    setlocale(LC_ALL, "Rus");
    do
        resolve();
    while (menu());
}

void sort() {
    for (int i = 0; i < 2; i++) {
        for (int t, j = 0; j < 2; j++) {
            if (abc[j] < abc[j + 1]) {
                t = abc[j];
                abc[j] = abc[j + 1];
                abc[j + 1] = t;
            }
        }
    }
}

void inputData() {
    abc[0] = 0;
    abc[1] = 0;
    abc[2] = 0;
    R = 0;
    printf("Условия задачи:\n");
    printf("Имеется 3 емкости объемами A, B, C. Наибольшая из них заполнена водой. Требуется отмерить R литров воды. Как это сделать, если воду нельзя проливать?\n");
    printf("Нажмите Enter, чтобы подтвердить ознакомление с условием и начать вводить исходные данные...\n");
    while (abc[0] < 1) {
        getchar();
        printf("A = ");
        scanf_s("%d", &abc[0]);
    }
    while (abc[1] < 1) {
        printf("B = ");
        getchar();
        scanf_s("%d", &abc[1]);
    }
    while (abc[2] < 1) {
        printf("C = ");
        getchar();
        scanf_s("%d", &abc[2]);
    }
    while (R < 1) {
        printf("R = ");
        getchar();
        scanf_s("%d", &R);
    }
    sort();
};

void printRes(int** res, int size) {
    printf("-------------------------------------------\n");
    printf("|   N | 1 емкость | 2 емкость | 3 емкость |\n");
    printf("-------------------------------------------\n");
    printf("| max | %9d | %9d | %9d |\n", abc[0], abc[1], abc[2]);
    printf("-------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("| %3d ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("| %9d ", res[i][j]);
        }
        printf("|\n");
    }
    printf("-------------------------------------------\n");
}

int checkRes(int* res) {
    if ((res[0] == R) || (res[1] == R) || (res[2] == R)) return 1;
    return 0;
}

int var1() {

    int i = 0;

    res1[i] = (int*)malloc(3 * sizeof(int));
    res1[i][0] = abc[0];
    res1[i][1] = 0;
    res1[i][2] = 0;

    while (1) {
        do {
            i++;
            res1 = (int**)realloc(res1, (i + 1) * sizeof(int*));
            res1[i] = (int*)malloc(3 * sizeof(int));
            res1[i][0] = res1[i - 1][0] - abc[2];
            res1[i][1] = res1[i - 1][1];
            res1[i][2] = abc[2];
            if (checkRes(res1[i])) return i + 1;

            i++;
            res1 = (int**)realloc(res1, (i + 1) * sizeof(int*));
            res1[i] = (int*)malloc(3 * sizeof(int));
            res1[i][0] = res1[i - 1][0];
            if (abc[1] - res1[i - 1][1] >= abc[2]) {
                res1[i][1] = res1[i - 1][1] + abc[2];
                res1[i][2] = 0;
            }
            else {
                res1[i][1] = abc[1];
                res1[i][2] = res1[i - 1][2] - (abc[1] - res1[i - 1][1]);
            }
            if (checkRes(res1[i])) return i + 1;

        } while (res1[i][1] != abc[1]);

        i++;
        res1 = (int**)realloc(res1, (i + 1) * sizeof(int*));
        res1[i] = (int*)malloc(3 * sizeof(int));
        res1[i][0] = res1[i - 1][0] + abc[1];
        res1[i][1] = 0;
        res1[i][2] = res1[i - 1][2];
        if (checkRes(res1[i])) return i + 1;

        i++;
        res1 = (int**)realloc(res1, (i + 1) * sizeof(int*));
        res1[i] = (int*)malloc(3 * sizeof(int));
        res1[i][0] = res1[i - 1][0];
        res1[i][1] = res1[i - 1][2];
        res1[i][2] = 0;
        if (checkRes(res1[i])) return i + 1;
    }
    return i + 1;
};

int var2() {

    int i = 0;

    res2[i] = (int*)malloc(3 * sizeof(int));
    res2[i][0] = abc[0];
    res2[i][1] = 0;
    res2[i][2] = 0;

    i++;
    res2 = (int**)realloc(res2, (i + 1) * sizeof(int*));
    res2[i] = (int*)malloc(3 * sizeof(int));
    res2[i][0] = res2[i - 1][0] - abc[1];
    res2[i][1] = abc[1];
    res2[i][2] = res2[i - 1][2];

    while (1) {
        while (res2[i][1] != 0) {
            i++;
            res2 = (int**)realloc(res2, (i + 1) * sizeof(int*));
            res2[i] = (int*)malloc(3 * sizeof(int));
            res2[i][0] = res2[i - 1][0];
            if (res2[i - 1][1] > abc[2] - res2[i - 1][2]) {
                res2[i][1] = res2[i - 1][1] - (abc[2] - res2[i - 1][2]);
                res2[i][2] = abc[2];
            }
            else {
                res2[i][1] = 0;
                res2[i][2] = res2[i - 1][1];
            }
            if (res2[i][1] == 0) break;
            if (checkRes(res2[i])) return i + 1;

            i++;
            res2 = (int**)realloc(res2, (i + 1) * sizeof(int*));
            res2[i] = (int*)malloc(3 * sizeof(int));
            res2[i][0] = res2[i - 1][0] + abc[2];
            res2[i][1] = res2[i - 1][1];
            res2[i][2] = 0;
            if (checkRes(res2[i])) return i + 1;

        }

        i++;
        res2 = (int**)realloc(res2, (i + 1) * sizeof(int*));
        res2[i] = (int*)malloc(3 * sizeof(int));
        res2[i][0] = res2[i - 1][0] - abc[1];
        res2[i][1] = abc[1];
        res2[i][2] = res2[i - 1][2];
        if (checkRes(res2[i])) return i + 1;
    }
    return i + 1;
};

void clear(int** res, int size) {
    for (int i = 0; i < size; i++) {
        free(res[i]);
    }
    free(res);
}

void resolve() {

    inputData();

    res1 = (int**)malloc(sizeof(int*));
    res2 = (int**)malloc(sizeof(int*));

    n1 = var1();
    n2 = var2();
}

int menu() {
    int choice = -1;
    while (1) {
        printf("Введите цифру для выбора одного из пуктов меню:\n");
        printf("1. Показать оптимальное решение\n");
        printf("2. Показать альтернативное решение\n");
        printf("3. Ввести другие данные\n");
        printf("0. Выход\n");

        scanf_s("%d", &choice);

        switch (choice)
        {
        case 1:
            if (n1 < n2) printRes(res1, n1);
            else printRes(res2, n2);
            break;
        case 2:
            if (n1 >= n2) printRes(res1, n1);
            else printRes(res2, n2);
            break;
        case 3:
            clear(res1, n1);
            clear(res2, n2);
            return 1;
        case 0:
            clear(res1, n1);
            clear(res2, n2);
            return 0;
        default:
            menu();
        }
    }
}