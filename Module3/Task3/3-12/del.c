#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* queue = (char*)malloc(sizeof(argv[1])+1);
    strcpy(queue, "/");
    strcat(queue, argv[1]);
    if (mq_unlink(queue) == -1) {
        perror("Queue remove");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}