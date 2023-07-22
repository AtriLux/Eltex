#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int fd = open("fifo", O_RDONLY);
    if (fd == -1) {
        perror("FIFO open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = getpid();
    while (1) {
        int num;
        if (read(fd, &num, sizeof(int)) == -1) {
            perror("FIFO read");
            exit(EXIT_FAILURE);
        }
        printf("Proccess %d read %d\n", pid, num);
    }
    close(fd);
}