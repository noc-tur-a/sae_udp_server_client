#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <poll.h>

#include "../errorCode.h"
#include "../sharedFunctions.h"
#include "clientFunctions.h"

//#define SERVER_PORT 18000
//#define TIMEOUT 10 * 1000
//#define MAX_CLIENTS 6
//typedef struct thread_data {
//    int addr;
//    unsigned long long result;
//} thread_data_t;

//long long current_timestamp();
//void* connectToPi(void* p_pi);

int main(int argc, char *argv[]) {

    printf("Before Threads\n");
    pthread_t thread_id_1;
    pthread_t thread_id_2;
    //pthread_t thread_id_3;

    thread_data_t tdata_pi_1;
    tdata_pi_1.addr = 1;

    thread_data_t tdata_pi_2;
    tdata_pi_2.addr = 2;

    //thread_data_t tdata_pi_3;
    //tdata_pi_2.addr = 3;

    unsigned long long timeStamp =  current_timestamp();
    printf("Current time: %llu\n", timeStamp);
    pthread_create(&thread_id_1, NULL, connectToPi, (void *)&tdata_pi_1);
    pthread_create(&thread_id_2, NULL, connectToPi, (void *)&tdata_pi_2);
    //pthread_create(&thread_id_3, NULL, connectToPi, (void *)&tdata_pi_3);

    pthread_join(thread_id_1, NULL);
    pthread_join(thread_id_2, NULL);
    //pthread_join(thread_id_3, NULL);



    printf("After Thread*************************************************\n");

    printf("After Thread tdata.result_1: %llu\n", tdata_pi_1.result);
    printf("After Thread tdata.result_2: %llu\n", tdata_pi_2.result);

    printf("PI1 difference: %llu\n", tdata_pi_1.result - timeStamp);
    printf("PI2 difference: %llu\n", tdata_pi_2.result - timeStamp);

}


//void* connectToPi(void* arg) {
//    printf("inside connectToPi\n");
//    long n;
//    thread_data_t *tdata = (thread_data_t *)arg;
//    tdata->result = 0;
//    char* measurePi;
//
//    if(tdata->addr == 1) {
//        measurePi = "192.168.8.210";
//    }else if (tdata->addr == 2) {
//        measurePi = "192.168.8.220";
//    }else if (tdata->addr == 3) {
//        measurePi = "192.168.8.230";
//    } else {
//        measurePi = "0.0.0.0";
//        //exit(EXIT_FAILURE);
//    }
//
//    struct sockaddr_in server;
//
//    server.sin_family =AF_INET;
//    server.sin_port = htons(SERVER_PORT);
//
//    int sock= socket(AF_INET, SOCK_DGRAM, 0);
//    if(sock < 0) {
//        printf("Error socket\n");
//    }
//
//    printf("Talking to Pi: %s\n", (char*) measurePi);
//
//    if(inet_pton(AF_INET, measurePi, &server.sin_addr) <= 0) {
//        //TODO ErrorHandling
//        printf("[CL] can't convert IP address\n");
//    }
//
//    struct pollfd pollfds[MAX_CLIENTS + 1];
//    pollfds[0].fd = sock;
//    pollfds[0].events = POLLIN | POLLPRI;
//    int useClient = 0;
//
//    unsigned int serverLength=sizeof(struct sockaddr_in);
//    char* buffer = "Send me stuff";
//    char receiveBuffer[256];
//    n = sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *) &server, serverLength);
//    if (n < 0) {
//        printf("Error Sendto\n");
//        exit(EXIT_FAILURE);
//    }
//
//    int pollResult = poll(pollfds, useClient + 1, TIMEOUT);
//    if (pollResult > 0) {
//        //printf("poll success\n");
//        n = recvfrom(sock, receiveBuffer, 256, 0, (struct sockaddr *) &server, &serverLength);
//        if (n < 0) {
//            printf("Error recvfrom");
//        } else {
//            char *b;
//            tdata->result = strtol(receiveBuffer, &b, 10);
//            printf("Message received tdata->result: %llu\n", tdata->result);
//        }
//    } else {
//        printf("TIMEOUT reached. Server not responding giving up\n");
//    }
//
//
//    //pthread_exit(NULL);
//    return NULL;
//}


