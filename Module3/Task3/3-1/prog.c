#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE* f;
    int i = 0;
    while (1) {
        f = fopen("res.txt", "a");
        if (!f) {
            perror("Open file");
            exit(EXIT_FAILURE);
        }
        fprintf(f, "%d\n", i);
        fclose(f);
        i++;
        sleep(1000);
    }
}