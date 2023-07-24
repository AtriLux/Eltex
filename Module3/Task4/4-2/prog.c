#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *_buf;
};

int main(int argc, char* argv[]) {
    if (argc == 1) {
        puts("Empty arguments");
        exit(EXIT_FAILURE);
    }
    //create file
    int cr = creat("result.txt", S_IRUSR | S_IWUSR);
    close(cr);

    //create semaphore 
    key_t key = ftok(".", '#');
    int sid = semget(key, 1, 0666 | IPC_CREAT);
    struct sembuf lock = {0, -1, 0};
    struct sembuf unlock[2] = {{0, 0, 0}, {0, 1, 0}};
    union semun ar;
    ar.val = 1;
    if (semctl(sid, 0, SETVAL, ar) == -1) {
        perror("Semaphore create");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int fd[2];
    int len = strtol(argv[1], NULL, 10);
    if (pipe(fd) == -1) {
        perror("Pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("Fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            for (int i = 0; i < len; i++) {
                
                if (semop(sid, &lock, 1) == -1) { // lock file
                    perror("Lock file");
                    exit(EXIT_FAILURE);
                }

                //open file
                int file = open("result.txt", O_RDONLY);
                if (file == -1) {
                    perror("Open file");
                    exit(EXIT_FAILURE);
                }

                //print from file
                printf("\nFile:\n");
                int code;
                do {
                char c;
                code = read(file, &c, sizeof(c));
                if (code == -1) {
                    perror("Read file");
                    exit(EXIT_FAILURE);
                }
                printf("%c", c);
                } while (code);

                close(file);

                if (semop(sid, unlock, 2) == -1) { // unlock file
                    perror("Unlock file");
                    exit(EXIT_FAILURE);
                }

                //write new num
                int num = rand() % 10;
                write(fd[1], &num, sizeof(int));
            }
            close(fd[1]);
            exit(EXIT_SUCCESS);
            break;
        default:
            for (int i = 0; i < len; i++) {

                // read new num
                int num;
                read(fd[0], &num, sizeof(int));
                printf("Num: %d\n", num);

                if (semop(sid, &lock, 1) == -1) { // lock file
                    perror("Lock file");
                    exit(EXIT_FAILURE);
                }

                //open file
                int file = open("result.txt", O_WRONLY | O_APPEND);
                if (file == -1) {
                    perror("Open file");
                    exit(EXIT_FAILURE);
                }

                //write to file
                char c = num + '0';
                write(file, &c, 1);
                write(file, "\n", 1);
                close(file);

                usleep(1000);
                if (semop(sid, unlock, 2) == -1) { // unlock file
                    perror("Unlock file");
                    exit(EXIT_FAILURE);
                }
            }
            close(fd[0]);
            exit(EXIT_SUCCESS);
            break;
    }
}