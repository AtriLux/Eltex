#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

typedef struct msgbuf {
    long mtype;
    char mtext[2];
} msgbuf;

int main() {
    srand(time(NULL));
    key_t key = ftok(".", '#');
    if (key == -1) {
        perror("Key generate");
        exit(EXIT_FAILURE);
    }
    int id = msgget(key, IPC_CREAT | 0660);
    if (id == -1) {
        perror("Queue create/open");
        exit(EXIT_FAILURE);
    }

    int i = 250;
    while (i < 256) {
        int num = rand() % 10;
        printf("%d\n", num);
        msgbuf buf = {i, num + '0'};
        if (msgsnd(id, &buf, sizeof(buf.mtext), 0) == -1) {
            perror("Message send");
            exit(EXIT_FAILURE);
        }
        i++;
        sleep(1);
    }
}