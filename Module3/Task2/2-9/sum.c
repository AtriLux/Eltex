#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    const int size = 100;
    char buf[size];
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        sum += strtol(argv[i], NULL, 10);
    }
    while (fgets(buf, size, stdin)) {
        char* str = strtok(buf, " ");
        while (str) {
            sum += *str - '0';
            str = strtok(NULL, " ");
        }
    }
    printf("%d\n", sum);
}