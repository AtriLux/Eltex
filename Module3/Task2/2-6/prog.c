#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void returnBack(char* path) {
    char *c = &path[strlen(path)];
    while (*c != '/') c--;
    if (c > path) *c = '\0';
    return;
}

void next(char* path) {
    char choice[100];
    printf(">");
    fgets(choice, 99, stdin);
    choice[strlen(choice)-1] = '\0';
    if (!strcmp(choice, "exit")) {
        exit(EXIT_FAILURE);
    }
    if (!strcmp(choice, "..")) {
        returnBack(path);
    }
    else if (strcmp(choice, ".")) {
        strcat(path, "/");
        strcat(path, choice);
    }
}

int main(int argc, char* argv[]) {

    char directory[NAME_MAX] = "/";

    while (1) {
        DIR* d = opendir(directory);
        if (!d) {
            puts("Wrong directory. Try again\n");
            returnBack(directory);
            next(directory);
        }
        else {
            system("clear");
            printf("LOCATION: %s\n\n", directory)
            struct dirent* n;
            while (n = readdir(d)) {
                printf("%-30s\t|\t", n->d_name);

                struct stat st;
                char pathfile[strlen(n->d_name) + strlen(directory) + 2];
                strcpy(pathfile, directory);
                if (!strcmp(directory, "/"));
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
            puts("");
            next(directory);
            closedir(d);
        }
    }
}