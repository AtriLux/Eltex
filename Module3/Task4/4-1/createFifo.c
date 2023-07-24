#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *_buf;
};

int main() {
    //SEM
    key_t key = ftok(".", '#');
    int sid = semget(key, 1, 0666 | IPC_CREAT);
    union semun ar;
    ar.val = 1;
    if (semctl(sid, 0, SETVAL, ar) == -1) {
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