#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    unlink("fifo");
    if (mkfifo("fifo", 0666) == -1) {
        perror("FIFO create");
        exit(EXIT_FAILURE);
    }
}