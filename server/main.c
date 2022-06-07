#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include "../errorCode.h"
#include "../sharedFunctions.h"

#define MAX_LENGTH 50
//TODO refactor

int main() {

    srand(time(0));

    int sock, length;
    long sendReceiveSuccess;
    unsigned int fromLength;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char bufferReceive[MAX_LENGTH];
    char bufferSend[MAX_LENGTH];

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printError(SOCKET_ERROR);
        exit(EXIT_FAILURE);
    }

    length = sizeof(server);
    bzero(&server,length);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(SERVER_PORT);
    if (bind(sock,(struct sockaddr *)&server,length) < 0)
    {
        printError(BIND_ERROR);
        exit(EXIT_FAILURE);
    }


    fromLength = sizeof(struct sockaddr_in);
    while(true) {
        sendReceiveSuccess = recvfrom(sock, bufferReceive, MAX_LENGTH, 0, (struct sockaddr *)&from, &fromLength);
        if (sendReceiveSuccess < 0) {
            printError(RECEIVE_ERROR);
            exit(EXIT_FAILURE);
        }
        //Fake response, measurement takes time

        unsigned long long timeStampStart =  current_timestamp();

        //TODO implement sensor, delete mockup, if servers mic is malfunction server should send 0 or nothing at all
        printf("Received a datagram\n");
        int num = (rand() % (10 - 1 + 1)) + 1;
        //int num = (rand() % (10 - 9 + 1)) + 1;
        sleep(num);
        //End mockup

        unsigned long long timeStampEnd =  current_timestamp();
        sprintf(bufferSend, "%llu\n", timeStampEnd - timeStampStart);

        sendReceiveSuccess = sendto(sock, bufferSend, MAX_LENGTH, 0, (struct sockaddr *)&from, fromLength);
        if (sendReceiveSuccess < 0) {
            printError(SEND_ERROR);
            exit(EXIT_FAILURE);
        }
    }
}