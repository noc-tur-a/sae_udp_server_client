#ifndef SAE_SERVER_ERRORCODE_H
#define SAE_SERVER_ERRORCODE_H

typedef enum errorCode {
    SUCCESS,
    BIND_ERROR,
    LISTEN_ERROR,
    SOCKET_ERROR,
    READ_ERROR,
    INET_ADDR_ERROR,
    SEND_ERROR,
    RECEIVE_ERROR,
    TIMEOUT_REACHED,
    INVALID_IP_ADDRESS,
    INSUFFICIENT_DATA
} errorCode_t;

void printError(errorCode_t errorCode);
#endif //SAE_SERVER_ERRORCODE_H
