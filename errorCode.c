//
// Created by carpe on 05.06.22.
//

#include <stdio.h>
#include "errorCode.h"

/**
 * brief prints error codes
 * @param errorCode the actual error that occurred
 */
void printError(errorCode_t errorCode) {
    if(errorCode == BIND_ERROR) {
        printf("Can't Bind to address.\n");
    }
    if(errorCode == BIND_ERROR) {
        printf("Can't listen to address.\n");
    }
    if(errorCode == SOCKET_ERROR) {
        printf("Socket creation failed.\n");
    }
    if(errorCode == READ_ERROR) {
        printf("READ function error.\n");
    }
    if(errorCode == INET_ADDR_ERROR) {
        printf("Can't create IP Address.\n");
    }
    if(errorCode == SEND_ERROR) {
        printf("send function failed.\n");
    }
    if(errorCode == RECEIVE_ERROR) {
        printf("receive function failed.\n");
    }
    if(errorCode == TIMEOUT_REACHED) {
        printf("TIMEOUT reached. Server not responding...giving up...\n");
    }
    if(errorCode == INVALID_IP_ADDRESS) {
        printf("Invalid IP address passed.\n");
    }
    if(errorCode == INSUFFICIENT_DATA) {
        printf("Can't calculate result. Insufficient Data.\n");
    }

}

