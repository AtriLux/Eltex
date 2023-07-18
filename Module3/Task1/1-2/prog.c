#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void printEnd() {
    puts("End program");
}

int main(int argc, char* argv[]) {
    int wt;
    pid_t pid = fork();
    atexit(printEnd);
    switch (pid) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            for (int i = 0; i < argc; i++) {
                printf("CHILD: %d. %s\n", i, argv[i]);
            }
            exit(EXIT_SUCCESS);
            break;
        default:
            for (int i = 0; i < argc; i++) {
                printf("PARENT: %d. %s\n", i, argv[i]);
            }
            wait(&wt);
            exit(EXIT_SUCCESS);
            break;
    }
}