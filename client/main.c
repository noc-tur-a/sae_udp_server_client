#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "../errorCode.h"
#include "../sharedFunctions.h"
#include "clientFunctions.h"

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

    //TODO add 3 PI and calculate distance
    if(tdata_pi_1.result != 0 && tdata_pi_2.result != 0) {
        printf("PI1 difference: %llu\n", tdata_pi_1.result - timeStamp);
        printf("PI2 difference: %llu\n", tdata_pi_2.result - timeStamp);
        //printf("PI3 difference: %llu\n", tdata_pi_3.result - timeStamp);
    } else {
        printError(INSUFFICIENT_DATA);
    }

}