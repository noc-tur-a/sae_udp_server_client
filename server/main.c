#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "../errorCode.h"
#include "../sharedFunctions.h"

int main() {

    srand(time(0));

    int sock, length;
    long n;
    unsigned int fromLength;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];

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
    while(1) {
        n = recvfrom(sock, buf,1024,0,(struct sockaddr *)&from,&fromLength);
        if (n < 0) {
            //TODO error handling
            printf("recvfrom");
        }
        //Fake response, measurement takes time
        printf("Received a datagram\n");
        int num = (rand() % (10 - 1 + 1)) + 1;
        //int num = (rand() % (10 - 9 + 1)) + 1;
        sleep(num);

        char str[50];
        //unsigned long timeStamp = (unsigned long)time(NULL);
        unsigned long long timeStamp =  current_timestamp();
        sprintf(str, "%llu\n", timeStamp);

        n = sendto(sock, str, 49, 0, (struct sockaddr *)&from, fromLength);
        if (n < 0)
        {
            //TODO error handling
            printf("Error: sendto");
        }
    }
}