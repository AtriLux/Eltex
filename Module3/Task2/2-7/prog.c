#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        puts("Empty arguments");
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
                int num = rand() % 10;
                write(fd[1], &num, sizeof(int));
            }
            close(fd[1]);
            exit(EXIT_SUCCESS);
            break;
        default:
            int num[len];
            for (int i = 0; i < len; i++) {
                read(fd[0], &num[i], sizeof(int));
                printf("%d\n", num[i]);
            }
            close(fd[0]);
            //print file
            int file = open("result.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (file == -1) {
                perror("Open file");
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < len; i++) {
                char c = num[i] + '0';
                write(file, &c, 1);
                write(file, "\n", 1);
            }
            close(file);
            exit(EXIT_SUCCESS);
            break;
    }
}