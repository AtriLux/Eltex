#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int fd = open("fifo", O_WRONLY);
    if (fd == -1) {
        perror("FIFO open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = getpid();
    while (1) {
        int num = rand() % 10;
        write(fd, &num, sizeof(int));
        printf("Proccess %d write %d\n", pid, num);
        sleep(2);
    }
    close(fd);
}