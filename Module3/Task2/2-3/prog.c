#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

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
        printf("%s\n", n->d_name);
    }

    closedir(d);
}