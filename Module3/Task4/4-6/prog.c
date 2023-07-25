#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>


int main(int argc, char* argv[]) {
    if (argc == 1) {
        puts("Empty arguments");
        exit(EXIT_FAILURE);
    }
    //create file
    int cr = creat("result.txt", S_IRUSR | S_IWUSR);
    close(cr);

    //semaphores
    sem_unlink("/sem1");
    sem_t* sid_write = sem_open("/sem1", O_CREAT, 0666, 1);
    if (sid_write == SEM_FAILED) {
        perror("Semaphore 1 create");
        exit(EXIT_FAILURE);
    }
        sem_unlink("/sem2");
    sem_t* sid_read = sem_open("/sem2", O_CREAT, 0666, 3);
    if (sid_read == SEM_FAILED) {
        perror("Semaphore 2 create");
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
                
                if (sem_wait(sid_read) == -1) { // lock file
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
                
                sleep(1); // for tests
                if (sem_post(sid_read) == -1) { // unlock file
                    perror("Unlock FIFO");
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

                if (sem_wait(sid_write) == -1) { // lock file
                    perror("Lock FIFO");
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

                sleep(1); // for tests
                if (sem_post(sid_write) == -1) { // unlock file
                    perror("Unlock FIFO");
                    exit(EXIT_FAILURE);
                }
            }
            close(fd[0]);
            exit(EXIT_SUCCESS);
            break;
    }
}