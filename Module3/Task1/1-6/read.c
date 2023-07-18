#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int file = open(argv[1], O_RDONLY);
    if (!file) {
        perror("Open file");
        exit(EXIT_FAILURE);
    }
    int size = lseek(file, 0, SEEK_END);
    lseek(file, 0, SEEK_SET);

    char* buf = (char*)malloc(sizeof(char)*size);
    read(file, buf, size);
    puts(buf);

    close(file);
    free(buf);
}