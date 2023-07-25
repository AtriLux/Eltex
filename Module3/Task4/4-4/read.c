#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char* argv[]) {
    //semaphores
    //open
    sem_t* sid = sem_open("/sem", 0);
    if (sid == SEM_FAILED) {
        perror("Semaphore open");
        exit(EXIT_FAILURE);
    }

    //FIFO
    int fd = open("fifo", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("FIFO open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = getpid();
    while (1) {
        int num;
        if (sem_wait(sid) == -1) { // lock FIFO
            perror("Lock FIFO");
            exit(EXIT_FAILURE);
        }
        int isRead = read(fd, &num, sizeof(int));
        if (sem_post(sid) == -1) { // unlock FIFO
            perror("Unlock FIFO");
            exit(EXIT_FAILURE);
        }
        if (isRead != -1 && isRead != 0) printf("Proccess %d read %d\n", pid, num);
    }
    sem_close(sid);
    close(fd);
}