#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]) {

    if (argc == 1) {
        puts("Empty file");
        exit(EXIT_FAILURE);
    }
    DIR* d = opendir(".");
    if (!d) {
        perror("Open directory");
        exit(EXIT_FAILURE);
    }

    struct dirent* n;
    while (n = readdir(d)) {
        if (!strcmp(n->d_name, argv[1])) {
            break;
        }
    }

    closedir(d);

    int c;
    if (!n) {
        puts("File not found. Create file? [1-yes, 0-no, other-no]");
        scanf("%d", &c);
        if (c != 1) {
            puts("End program");
            exit(EXIT_SUCCESS);
        }
    }

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

    puts("Success");
    exit(EXIT_FAILURE);
}