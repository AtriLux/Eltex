#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main() {
    srand(time(NULL));
    //semaphors
    //open
    key_t key = ftok(".", '#');
    int sid = semget(key, 1, 0);
    //operations
    struct sembuf lock = {0, -1, 0};
    struct sembuf unlock[2] = {{0, 0, 0}, {0, 1, 0}};

    //FIFO
    int fd = open("fifo", O_WRONLY);
    if (fd == -1) {
        perror("FIFO open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = getpid();
    while (1) {
        int num = rand() % 10;
        if (semop(sid, &lock, 1) == -1) { // lock FIFO
            perror("Lock FIFO");
            exit(EXIT_FAILURE);
        }
        if (write(fd, &num, sizeof(int)) == -1) {
            perror("FIFO write");
            exit(EXIT_FAILURE);
        }
        if (semop(sid, unlock, 2) == -1) { // unlock FIFO
            perror("Unlock FIFO");
            exit(EXIT_FAILURE);
        }
        printf("Proccess %d write %d\n", pid, num);
        sleep(2);
    }
    close(fd);
}