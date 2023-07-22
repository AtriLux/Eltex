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
    int fd1[2], fd2[2];
    int len = strtol(argv[1], NULL, 10);
    if (pipe(fd1) == -1) {
        perror("Pipe 1");
        exit(EXIT_FAILURE);
    }
    if (pipe(fd2) == -1) {
        perror("Pipe 1");
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
                write(fd1[1], &num, sizeof(int));
                int ans;
                read(fd2[0], &ans, sizeof(int));
                printf("%d * 2 = %d\n", num, ans);
            }
            close(fd1[1]);
            close(fd2[0]);
            exit(EXIT_SUCCESS);
            break;
        default:
            int num[len];
            for (int i = 0; i < len; i++) {
                read(fd1[0], &num[i], sizeof(int));
                printf("%d\n", num[i]);
                int ans = num[i] * 2;
                write(fd2[1], &ans, sizeof(int));
            }
            close(fd1[0]);
            close(fd2[1]);
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