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

/**
 * brief: function used in the threads. connects to PI (servers) and waits for response
 * if no response comes it times out (TIMEOUT)
 * @param arg the arguments needed to connect to the PI and to store the result
 * @return NULL
 */
void* connectToPi(void* arg) {
    long sendReceiveStatus;
    thread_data_t *tdata = (thread_data_t *)arg;
    tdata->result = 0;
    const char* ipAddressPI;

    if(tdata->addr == 1) {
        ipAddressPI = "192.168.8.210";
    }else if (tdata->addr == 2) {
        ipAddressPI = "192.168.8.220";
    }else if (tdata->addr == 3) {
        ipAddressPI = "192.168.8.230";
    } else {
        //ipAddressPI = "0.0.0.0";
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

    printf("Talking to Pi: %s\n", (char*) ipAddressPI);

    if(inet_pton(AF_INET, ipAddressPI, &server.sin_addr) <= 0) {
        printError(INET_ADDR_ERROR);
        exit(EXIT_FAILURE);
    }

    struct pollfd pollfds[MAX_CLIENTS + 1];
    pollfds[0].fd = sock;
    pollfds[0].events = POLLIN | POLLPRI;
    int useClient = 0;

    unsigned int serverLength=sizeof(struct sockaddr_in);
    char* buffer = "Send me stuff"; //TODO command to send to the PIs (not really important what is send because the servers have only one job)
    char receiveBuffer[MAX_BUFFER_SIZE];
    sendReceiveStatus = sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *) &server, serverLength);
    if (sendReceiveStatus < 0) {
        printError(SEND_ERROR);
        exit(EXIT_FAILURE);
    }

    //if something is to poll we receive it with  recvfrom otherwise we run into the timeout
    int pollResult = poll(pollfds, useClient + 1, TIMEOUT);
    if (pollResult > 0) {
        //poll successful
        sendReceiveStatus = recvfrom(sock, receiveBuffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &server, &serverLength);
        if (sendReceiveStatus < 0) {
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