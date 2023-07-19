#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "w");
    if (!file) {
        perror("Open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 2; i < argc; i++) {
        fwrite(argv[i], strlen(argv[i]), 1, file);
        if (i != argc - 1) fwrite(" ", 1, 1, file);
    }
    fclose(file);
}