#ifndef SAE_SERVER_ERRORCODE_H
#define SAE_SERVER_ERRORCODE_H

typedef enum errorCode {
    SUCCESS,            /** function was successful **/
    BIND_ERROR,         /** binding error occurred **/
    LISTEN_ERROR,       /** listen error occurred **/
    SOCKET_ERROR,       /** socket creation failed **/
    READ_ERROR,         /** unable to read data **/
    INET_ADDR_ERROR,    /** wrong IP address was given **/
    SEND_ERROR,         /** unable to send data **/
    RECEIVE_ERROR,      /** unable to read data **/
    TIMEOUT_REACHED,    /** timeout was reached**/
    INVALID_IP_ADDRESS, /** couldn't translate IP address **/
    INSUFFICIENT_DATA,   /** PI couldn't povide data **/
    PERMANENT_ERROR     /** one or more PI isn't reachable for X MAX_NUMBER_OF_RETRIES amounts of retries **/
} errorCode_t;

//typedef enum {
//    SUCCESS,            /** function was successful **/
//    BIND_ERROR,         /** binding error occurred **/
//    LISTEN_ERROR,       /** listen error occurred **/
//    SOCKET_ERROR,       /** socket creation failed **/
//    READ_ERROR,         /** unable to read data **/
//    INET_ADDR_ERROR,    /** wrong IP address was given **/
//    SEND_ERROR,         /** unable to send data **/
//    RECEIVE_ERROR,      /** unable to read data **/
//    TIMEOUT_REACHED,    /** timeout was reached**/
//    INVALID_IP_ADDRESS, /** couldn't translate IP address **/
//    INSUFFICIENT_DATA,   /** PI couldn't povide data **/
//    PERMANENT_ERROR     /** one or more PI isn't reachable for X MAX_NUMBER_OF_RETRIES amounts of retries **/
//} errorCause;
//
//typedef struct errorCode {
//    errorCause errorCause;
//    int maxNumberOfRetries;
//} errorCode_t;

//struct errorCode {
//    errorCause errorCause;
//    struct  a {
//        int maxNumberOfRetries = 5;
//    };
//    //int maxNumberOfRetries = 5;
//};

void printError(errorCode_t errorCode);
//void printError(struct errorCode errorCode);
#endif //SAE_SERVER_ERRORCODE_H
