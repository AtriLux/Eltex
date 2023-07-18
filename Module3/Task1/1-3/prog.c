#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int wt, cnt;
    if (argc % 2 == 1) cnt = (argc+1) / 2;
    else cnt = argc / 2 + 1;
    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            for (int i = cnt; i < argc; i++) {
                int n = strtol(argv[i], NULL, 10);
                printf("CHILD: a = %d -> S = %d\n", n, n*n);
            }
            exit(EXIT_SUCCESS);
            break;
        default:
            for (int i = 1; i < cnt; i++) {
                int n = strtol(argv[i], NULL, 10);
                printf("PARENT: a = %d -> S = %d\n", n, n*n);
            }
            wait(&wt);
            exit(EXIT_SUCCESS);
            break;
    }
}