#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    int max = INT_MIN;
    for (int i = 2; i < argc; i++) {
        int n = strtol(argv[i], NULL, 10);
        if (n > max) max = n;
    }
    printf("max = %d\n", max);
}