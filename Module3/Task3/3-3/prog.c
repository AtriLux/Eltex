#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int wait = 1;

void sigAct(int sig) {
    static int cnt = 0;
    cnt++;
    if (cnt == 3) wait = 0;
}

int main() {
    signal(SIGINT, sigAct);
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