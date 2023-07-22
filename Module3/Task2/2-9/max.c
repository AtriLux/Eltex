#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main(int argc, char* argv[]) {
    const int size = 100;
    char buf[size];
    int max = INT_MIN;
    for (int i = 1; i < argc; i++) {
        int n = strtol(argv[i], NULL, 10);
        if (n > max) max = n;
    }
    while (fgets(buf, size, stdin)) {
        char* str = strtok(buf, " ");
        while (str) {
            if (*str - '0' > max) max = *str - '0';
            str = strtok(NULL, " ");
        }
    }
    printf("%d\n", max);
}