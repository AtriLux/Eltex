#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void delFirstSpace(char** copy) {
    int space = strcspn(*copy, " ");
    if (!space) {
        memmove(*copy, *copy + 1, strlen(*copy));
    }
}

void delLastSpace(char** copy) {
    int space = strcspn(*copy, " ");
    int len = strlen(*copy);
    if (space == len - 1) {
        memmove(*copy + len - 1, *copy + len, 2);
    }
}

void strBeforeSpace(char** copy, char** str) {
    int space = strcspn(*copy, " ");
    if (!space) { // if copy has last word
        *str = (char*)malloc(sizeof(char)*(strlen(*copy)+1));
        memmove(*str, *copy, strlen(*copy) + 1);
        strcpy(*copy, " ");
    }
    else {
        *str = (char*)malloc(sizeof(char)*(space+1));
        memmove(*str, *copy, space);
        memmove(*copy, *copy + space, strlen(*copy) - space + 1);
        *(str + space) = '\0';
    }
}

int main(int argc, char* argv[]) { // argv = "ls | head -3 | tail -1"
    int w;
    if (argc == 1) {
        puts("Empty parameters");
        exit(EXIT_FAILURE);
    }
    int fd1[2];
    int fd2 = 0;
    char* commands = strtok(argv[1], "|"); // commands = "ls", "head -3", "tail -1"
    while (commands) {

        char* path;
        char* arg[10];

        char* copy = (char*)malloc(sizeof(char)*(strlen(commands)+2)); 
        strcpy(copy, commands);

        int j = 0;
        while (1) {
            char* str;
            delFirstSpace(&copy);
            strBeforeSpace(&copy, &str);
            delFirstSpace(&str);
            delLastSpace(&str);
            if (strcmp(str, "")) {
                arg[j] = str;
                j++;
                if (!strcmp(copy, " ") || !strcmp(copy, "\n") || !copy)
                    break;
            }
            else break;
        }

        arg[j] = NULL;

        if (!strcmp(arg[0],"max") || !strcmp(arg[0],"sum")) {
            path = arg[0];
        }
        else {
            char absPath[30] = "/bin/";
            strcat(absPath, arg[0]);
            path = absPath;
        }

        arg[0] = path;

        //print arguments
        /*for (int i = 0; i < 10; i++) {
            printf("%d. |%s|\n", i, arg[i]);
            if (!arg[i]) break;
        }*/

        if (pipe(fd1) == -1) {
            perror("Pipe");
            exit(EXIT_FAILURE);
        } 

        pid_t pid = fork();
        switch (pid) {
            case -1:
                perror("Fork");
                exit(EXIT_FAILURE);
                break;
            case 0: // child
                //printf("\n%s: r-%d, w-%d\n", arg[0], fd2, fd1[1]);
                if (dup2(fd2, 0) == -1) {
                    perror("Stdin");
                    exit(EXIT_FAILURE);
                }
                if (strtok(NULL, "|")) {
                    if (dup2(fd1[1], 1) == -1) {
                        perror("Stdout");
                        exit(EXIT_FAILURE);
                    }
                }
                if (execv(path, arg) == -1) {
                    perror("EXE");
                    exit(EXIT_FAILURE);
                }
                printf("\n%s: r-%d, w-%d\n", arg[0], fd2, fd1[1]);
                exit(EXIT_SUCCESS);
            default: // parent
                wait(&w);
                fd2 = fd1[0];
                commands = strtok(NULL, "|");
        }
    }
    exit(EXIT_SUCCESS);
}