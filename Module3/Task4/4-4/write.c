#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>

int main() {
    srand(time(NULL));
    //semaphores
    //open
    sem_t* sid = sem_open("/sem", 0);
    if (sid == SEM_FAILED) {
        perror("Semaphore open");
        exit(EXIT_FAILURE);
    }

    //FIFO
    int fd = open("fifo", O_WRONLY);
    if (fd == -1) {
        perror("FIFO open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = getpid();
    while (1) {
        int num = rand() % 10;
        if (sem_wait(sid) == -1) { // lock FIFO
            perror("Lock FIFO");
            exit(EXIT_FAILURE);
        }
        if (write(fd, &num, sizeof(int)) == -1) {
            perror("FIFO write");
            exit(EXIT_FAILURE);
        }
        if (sem_post(sid) == -1) { // unlock FIFO
            perror("Unlock FIFO");
            exit(EXIT_FAILURE);
        }
        printf("Proccess %d write %d\n", pid, num);
        sleep(2);
    }
    sem_close(sid);
    close(fd);
}