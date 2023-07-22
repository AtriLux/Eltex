#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

int wait = 0;

void fileBusy(int sig) {
    wait = 1;
}

void fileFree(int sig) {
    wait = 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        puts("Empty arguments");
        exit(EXIT_FAILURE);
    }
    //create file
    int cr = creat("result.txt", S_IRUSR | S_IWUSR);
    close(cr);

    //sreate signal-listener
    signal(SIGUSR1, fileBusy);
    signal(SIGUSR2, fileFree);

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
                //wait until file free
                while (wait) {}

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

                //send signal
                kill(0, SIGUSR1);

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

                //send signal
                usleep(1000);
                //sleep(1);
                kill(0, SIGUSR2);
            }
            close(fd[0]);
            exit(EXIT_SUCCESS);
            break;
    }
}