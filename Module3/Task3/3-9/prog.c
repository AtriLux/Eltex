#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

typedef struct msgbuf {
    long mtype;
    char mtext[100];
} msgbuf;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Count of arguments not valid\n");
        exit(EXIT_FAILURE);
    }

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

    int client = strtol(argv[1], NULL, 10);
    int online = 1;
    if (client == 1) { // server
        int clients[100] = { 0 };
        int i = 0;
        while (online) {
            msgbuf buf;
            msgrcv(id, &buf, sizeof(buf.mtext), client, 0); // wait client's msg
            char* new;
            int newClient = strtol(buf.mtext, &new, 10);
            if (*new == 0) { // new client connected
                char isNew = 1;
                for (int j = 0; j < 100; j++) { // check new client in old clients
                    if (clients[j] == newClient) { // if new client is old client
                        isNew = 0;
                        break;
                    }
                    if (!clients[j]) break; // if old clients finish
                }
                if (isNew) {
                    if (i == 99) i = 0; // rewrite old client
                    clients[i++] = newClient; // remember new client
                    buf.mtype = newClient;
                    msgsnd(id, &buf, sizeof(buf.mtext), 0); // send to new client
                }
            }
            else { // message from clients
                char* space = strchr(buf.mtext, ' ');
                if (space) { // if message has correct pattern
                    char clientStr[20];
                    int pos = space - buf.mtext; // position username before space
                    strncpy(clientStr, buf.mtext, pos); // copy msg without username
                    clientStr[pos] = '\0';
                    int clientId = strtol(clientStr, NULL, 10); // check client_id

                    int len = strlen(buf.mtext) - pos; // length msg without username
                    memcpy(buf.mtext, space + 1, len); // change msg
                    buf.mtext[len] = '\0';

                    if (clientId > 1) { // personal msg
                        buf.mtype = clientId;
                        msgsnd(id, &buf, sizeof(buf.mtext), 0); // send to username
                    }
                    else { // everyone msg
                        for (int i = 0; i < 100; i++) {
                            if (!clients[i]) break;
                            buf.mtype = clients[i];
                            msgsnd(id, &buf, sizeof(buf.mtext), 0); // send all username
                        }
                    }
                }
            }
        }
    }
    else { // clients
        // check server
        msgbuf check = {1, client + '0'};
        if (msgsnd(id, &check, sizeof(check.mtext), 0) == -1) {
            perror("Server check");
            exit(EXIT_FAILURE);
        }
        printf("\nTrying connect to server...\n");
        msgrcv(id, &check, sizeof(check.mtext), client, 0);
        
        while (online) {
            printf("\n\nChoose action:\n");
            printf("1. Send message to user [pattern: toUser message]\n");
            printf("2. Check new message from users\n");
            printf("3. Exit\n\n");

            int ch;
            printf("> ");
            scanf("%d", &ch);
            getchar();

            switch(ch) {
                case 1: { //send
                    long username;
                    msgbuf buf;
                    buf.mtype = 1;
                    printf("\n%d> ", client);
                    fgets(buf.mtext, sizeof(buf.mtext), stdin);

                    if (msgsnd(id, &buf, sizeof(buf.mtext), 0) == -1) {
                        perror("Message send");
                        exit(EXIT_FAILURE);
                    }
                    break;
                }
                case 2: { //receive
                    msgbuf buf;
                    while (msgrcv(id, &buf, sizeof(buf.mtext), client, IPC_NOWAIT) != -1) {
                        printf("\n< %s", buf.mtext);
                    }
                    printf("\nNo more new message");   
                    break;
                }
                case 3:
                    online = 0;
                    continue;
                default:
                    continue;
            }
        }
    }
}