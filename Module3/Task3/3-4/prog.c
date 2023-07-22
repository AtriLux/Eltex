#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int wait = 1;

void sigAct(int sig) {
    wait = 0;
    printf("Signal %d kill process\n", sig);
}

int main() {
    signal(SIGINT, sigAct);
    signal(SIGQUIT, sigAct);
    FILE* f;
    int i = 0;
    while (wait) {
        f = fopen("res.txt", "a");
        if (!f) {
            perror("Open file");
            exit(EXIT_FAILURE);
        }
        fprintf(f, "%d\n", i);
        fclose(f);
        i++;
        sleep(1);
    }
}