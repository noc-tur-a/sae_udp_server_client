#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include "../errorCode.h"
#include "clientFunctions.h"
#include "../sharedFunctions.h"

void* connectToPi(void* arg) {
    printf("inside connectToPi\n");
    long n;
    thread_data_t *tdata = (thread_data_t *)arg;
    tdata->result = 0;
    char* measurePi;

    if(tdata->addr == 1) {
        measurePi = "192.168.8.210";
    }else if (tdata->addr == 2) {
        measurePi = "192.168.8.220";
    }else if (tdata->addr == 3) {
        measurePi = "192.168.8.230";
    } else {
        //measurePi = "0.0.0.0";
        printError(INVALID_IP_ADDRESS);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;

    server.sin_family =AF_INET;
    server.sin_port = htons(SERVER_PORT);

    int sock= socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        printError(SOCKET_ERROR);
        exit(EXIT_FAILURE);
    }

    printf("Talking to Pi: %s\n", (char*) measurePi);

    if(inet_pton(AF_INET, measurePi, &server.sin_addr) <= 0) {
        //TODO ErrorHandling
        printError(INET_ADDR_ERROR);
        exit(EXIT_FAILURE);
    }

    struct pollfd pollfds[MAX_CLIENTS + 1];
    pollfds[0].fd = sock;
    pollfds[0].events = POLLIN | POLLPRI;
    int useClient = 0;

    unsigned int serverLength=sizeof(struct sockaddr_in);
    char* buffer = "Send me stuff";
    char receiveBuffer[256];
    n = sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *) &server, serverLength);
    if (n < 0) {
        printError(SEND_ERROR);
        exit(EXIT_FAILURE);
    }

    int pollResult = poll(pollfds, useClient + 1, TIMEOUT);
    if (pollResult > 0) {
        //poll successful
        n = recvfrom(sock, receiveBuffer, 256, 0, (struct sockaddr *) &server, &serverLength);
        if (n < 0) {
            printError(RECEIVE_ERROR);
            exit(EXIT_FAILURE);
        } else {
            char *b;
            tdata->result = strtol(receiveBuffer, &b, 10);
            printf("Message received tdata->result: %llu\n", tdata->result);
        }
    } else {
        printError(TIMEOUT_REACHED);
    }

    return NULL;
}