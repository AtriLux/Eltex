#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        puts("Empty directory");
        exit(EXIT_FAILURE);
    }
    DIR* d = opendir(argv[1]);
    if (!d) {
        perror("Open directory");
        exit(EXIT_FAILURE);
    }

    struct dirent* n;
    while (n = readdir(d)) {
        printf("%-30s\t|\t", n->d_name);

        struct stat st;
        char pathfile[strlen(n->d_name) + strlen(argv[1]) + 2];
        strcpy(pathfile, argv[1]);
        strcat(pathfile, "/");
        strcat(pathfile, n->d_name);
        strcat(pathfile, "\0");

        if (stat(pathfile, &st) == -1) {
            perror("Stat fail");
            exit(EXIT_FAILURE);
        }
        if (S_ISREG(st.st_mode))
            puts("file");
        else if (S_ISDIR(st.st_mode))
            puts("dir");
        else
            puts("other");

    }

    closedir(d);
}