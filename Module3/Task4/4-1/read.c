#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    //semaphors
    //open
    key_t key = ftok(".", '#');
    int sid = semget(key, 1, 0);
    //operations
    struct sembuf lock = {0, -1, 0};
    struct sembuf unlock[2] = {{0, 0, 0}, {0, 1, 0}};

    //FIFO
    int fd = open("fifo", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("FIFO open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = getpid();
    while (1) {
        int num;
        if (semop(sid, &lock, 1) == -1) { // lock FIFO
            perror("Lock FIFO");
            exit(EXIT_FAILURE);
        }
        int isRead = read(fd, &num, sizeof(int));
        if (semop(sid, unlock, 2) == -1) { // unlock FIFO
            perror("Unlock FIFO");
            exit(EXIT_FAILURE);
        }
        if (isRead != -1 && isRead != 0) printf("Proccess %d read %d\n", pid, num);
    }
    close(fd);
}