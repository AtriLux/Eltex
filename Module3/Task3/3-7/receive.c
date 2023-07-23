#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>

typedef struct msgbuf {
    long mtype;
    char mtext[2];
} msgbuf;

int main() {
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

    while (1) {
        msgbuf buf;
        if (msgrcv(id, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("Message receive");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", buf.mtext);
        if (buf.mtype == 255) break;
    }
    
    if (msgctl(id, IPC_RMID, NULL) == -1) {
        perror("Queue remove");
        exit(EXIT_FAILURE);
    }
}