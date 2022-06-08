#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "../errorCode.h"
#include "../sharedFunctions.h"
#include "clientFunctions.h"

//#define MAX_NUMBER_OF_RETRIES 6

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

    //int number_of_retries = 0;
    int numberOfCurrentRetriesPi_1 = 0;
    int numberOfCurrentRetriesPi_2 = 0;
    //int numberOfCurrentRetriesPi_3 = 0;
    while (numberOfCurrentRetriesPi_1 < MAX_NUMBER_OF_RETRIES && numberOfCurrentRetriesPi_2 < MAX_NUMBER_OF_RETRIES) {

        //TODO propably not needed, PIs are sending the measured time difference
        unsigned long long timeStamp = current_timestamp();

        printf("Current time: %llu\n", timeStamp);
        pthread_create(&thread_id_1, NULL, connectToPi, (void *) &tdata_pi_1);
        pthread_create(&thread_id_2, NULL, connectToPi, (void *) &tdata_pi_2);
        //pthread_create(&thread_id_3, NULL, connectToPi, (void *)&tdata_pi_3);

        pthread_join(thread_id_1, NULL);
        pthread_join(thread_id_2, NULL);
        //pthread_join(thread_id_3, NULL);

        printf("After Thread*************************************************\n");

        printf("After Thread tdata.result_1: %llu\n", tdata_pi_1.result);
        printf("After Thread tdata.result_2: %llu\n", tdata_pi_2.result);

        //TODO add 3 PI and calculate distance
        if (tdata_pi_1.result != 0 && tdata_pi_2.result != 0) {
            printf("PI1 measured: %llu\n", tdata_pi_1.result);
            printf("PI2 measured: %llu\n", tdata_pi_2.result);
            //printf("PI3 difference: %llu\n", tdata_pi_3.result - timeStamp);
            numberOfCurrentRetriesPi_1 = 0;
            numberOfCurrentRetriesPi_2 = 0;
            //numberOfCurrentRetriesPi_3 = 0;
        } else {
            if(tdata_pi_1.result == 0) {
                numberOfCurrentRetriesPi_1++;
                printInsufficientDataError(numberOfCurrentRetriesPi_1, INSUFFICIENT_DATA_PI_1);
                //numberOfCurrentRetriesPi_1++;
                //printError(INSUFFICIENT_DATA_PI_1);
                //printf("\nRetry %d / %d\n", numberOfCurrentRetriesPi_1, (MAX_NUMBER_OF_RETRIES - 1));
            }
            if(tdata_pi_2.result == 0) {
                numberOfCurrentRetriesPi_2++;
                printInsufficientDataError(numberOfCurrentRetriesPi_2, INSUFFICIENT_DATA_PI_2);

//                numberOfCurrentRetriesPi_2++;
//                printError(INSUFFICIENT_DATA_PI_2);
//                printf("\nRetry %d / %d\n", numberOfCurrentRetriesPi_2, (MAX_NUMBER_OF_RETRIES - 1));
            }
//            if(tdata_pi_3.result == 0) {
//                  numberOfCurrentRetriesPi_3++;
//                printInsufficientDataError(&numberOfCurrentRetriesPi_3, INSUFFICIENT_DATA_PI_3);
//            }

            if(numberOfCurrentRetriesPi_1 >= MAX_NUMBER_OF_RETRIES) {
                printError(PERMANENT_ERROR_PI_1);
            }
            if(numberOfCurrentRetriesPi_2 >= MAX_NUMBER_OF_RETRIES) {
                printError(PERMANENT_ERROR_PI_2);
            }
//            if(numberOfCurrentRetriesPi_3 >= MAX_NUMBER_OF_RETRIES) {
//                printError(PERMANENT_ERROR_PI_3);
//            }

            if(numberOfCurrentRetriesPi_1 >= MAX_NUMBER_OF_RETRIES || numberOfCurrentRetriesPi_2 >= MAX_NUMBER_OF_RETRIES) {
                break;
            }

            //printf("\nRetry %d / %d\n", numberOfCurrentRetriesPi_1, (MAX_NUMBER_OF_RETRIES - 1));
        }
    }
}