#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file == -1) {
        perror("Open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 2; i < argc; i++) {
        write(file, argv[i], strlen(argv[i]));
        if (i != argc - 1) write(file, " ", 1);
    }
    close(file);
}