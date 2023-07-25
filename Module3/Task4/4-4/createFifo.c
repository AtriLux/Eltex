#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

int main() {
    //SEM
    sem_unlink("/sem");
    if (sem_open("/sem", O_CREAT, 0666, 1) == SEM_FAILED) {
        perror("Semaphore create");
        exit(EXIT_FAILURE);
    }

    //FIFO
    unlink("fifo");
    if (mkfifo("fifo", 0666) == -1) {
        perror("FIFO create");
        exit(EXIT_FAILURE);
    }
}