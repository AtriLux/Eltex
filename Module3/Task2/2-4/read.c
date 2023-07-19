#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
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
        else {
            FILE* file = fopen(argv[1], "w");
            fclose(file);
            puts("Empty file created");
            exit(EXIT_SUCCESS);
        }
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Open file");
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buf = (char*)malloc(sizeof(char)*size);
    fread(buf, 1, size, file);
    puts(buf);

    fclose(file);
    free(buf);
}