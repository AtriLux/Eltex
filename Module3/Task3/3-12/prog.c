#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Count of arguments not valid\n");
        exit(EXIT_FAILURE);
    }
    int client = strtol(argv[1], NULL, 10);
    if (client < 1 || client > 9) {
        printf("Invalid ID. Enter ID between 1 and 9\n");
        exit(EXIT_FAILURE);
    }

    char* readQueue = (char*)malloc(sizeof(argv[1])+1);
    strcpy(readQueue, "/");
    strcat(readQueue, argv[1]);
    mqd_t readId = mq_open(readQueue, O_CREAT | O_RDONLY, 0660, NULL);
    if (readId == -1) {
        perror("Read queue create/open");
        exit(EXIT_FAILURE);
    }
    struct mq_attr at;
    mq_getattr(readId, &at);
    long size = at.mq_msgsize;

    int online = 1;
    if (client == 1) { // server
        int clients[8] = { 0 };
        mqd_t writeId[8] = { 0 };
        int i = 0;
        while (online) {
            int p;
            char buf[size];
            if (mq_receive(readId, buf, sizeof(buf), &p) == -1) { // wait client's msg
                perror("Server receive");
                exit(EXIT_FAILURE);
            }
            if (!strcmp(buf, " ")) { // new client connected
                char isNew = 1;
                for (int j = 0; j < 8; j++) { // check new client in old clients
                    if (clients[j] == p) { // if new client is old client
                        isNew = 0;
                        break;
                    }
                    if (!clients[j]) break; // if old clients finish
                }
                if (isNew) {
                    clients[i] = p; // remember new client

                    //open new queue
                    char writeQueue[2];
                    writeQueue[0] = '/';
                    writeQueue[1] = p + '0';
                    writeId[i] = mq_open(writeQueue, O_CREAT | O_WRONLY, 0660, NULL);
                    if (writeId[i] == -1) {
                        perror("Write queue create/open");
                        exit(EXIT_FAILURE);
                    }

                    mq_send(writeId[i++], " ", 2, 1); // send to new client
                }
            }
            else { // message from clients
                char* space = strchr(buf, ' ');
                if (space) { // if message has correct pattern
                    char clientStr[2]; // for destination client_id
                    clientStr[0] = buf[0];
                    clientStr[1] = '\0';
                    int clientId = strtol(clientStr, NULL, 10); // check client_id

                    int len = strlen(buf) - 2; // length msg without username
                    memcpy(buf, space + 1, len); // change msg
                    buf[len] = '\0';

                    if (clientId > 1) { // personal msg
                        //find writeId
                        int k;
                        for (k = 0; k < 8; k++) {
                            if (clients[k] == clientId) break;
                        }
                        
                        if (mq_send(writeId[k], buf, sizeof(buf), p) == -1) { // send to usernames
                            perror("Message sending to user");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else { // everyone msg
                        for (int i = 0; i < 8; i++) {
                            if (!clients[i]) break;
                            if (mq_send(writeId[i], buf, sizeof(buf), p) == -1) { // send all username
                                perror("Message sending to user");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }
        }
    }
    else { // clients
        mqd_t writeId = mq_open("/1", O_CREAT | O_WRONLY, 0660, NULL);
        if (writeId == -1) {
            perror("Write queue create/open");
            exit(EXIT_FAILURE);
        }
        // check server
        if (mq_send(writeId, " ", 2, client) == -1) {
            perror("Send server check");
            exit(EXIT_FAILURE);
        }
        printf("\nTrying connect to server...");

        char check[size];
        if (mq_receive(readId, check, sizeof(check), NULL) == -1) {
            perror("Receive server check");
            exit(EXIT_FAILURE);
        }
        
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
                    char buf[size];
                    printf("\n%d> ", client);
                    fgets(buf, sizeof(buf), stdin);

                    if (mq_send(writeId, buf, sizeof(buf), client) == -1) {
                        perror("Message send");
                        exit(EXIT_FAILURE);
                    }
                    break;
                }
                case 2: { //receive
                    char buf[size];
                    int p;

                    mq_getattr(readId, &at);
                    while (at.mq_curmsgs > 0) {
                        mq_receive(readId, buf, sizeof(buf), &p);
                        printf("\n%d> %s", p, buf);
                        mq_getattr(readId, &at);
                    }
                    printf("\nNo more new message\n");
                    break;
                }
                case 3:
                    online = 0;
                    if (mq_close(readId) == -1) {
                        perror("Read queue close");
                        exit(EXIT_FAILURE);
                    }
                    if (mq_close(writeId) == -1) {
                        perror("Write queue close");
                        exit(EXIT_FAILURE);
                    }
                    continue;
                default:
                    continue;
            }
        }
    }
}