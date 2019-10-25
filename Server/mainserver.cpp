#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h>
#include <string.h>
#include "newserver.h"
using namespace std;
void *review(void *x)
{
    // long j = (long)x;
    while (1)
    {
        for (int i = 0; i < 5; i++)
        {
            cout <<(long) x << endl;
        }
        sleep(2);
    }
    
}
int main(int argc, char *argv[])
{
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client[5];
    long cli[5];

    //Create socket

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        cout << "Cannot create the socket" << endl;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    cout << "Bind done" << endl;

    cout << "Waiting for the incoming connections" << endl;
    c = sizeof(struct sockaddr_in);
    listen(socket_desc, 3);
    //Creating a thread variable
    pthread_t threadid[5];
    pthread_t dispThread;
    int i = 0;
    //pthread_create(&dispThread, NULL, review, (void *)&cli);
    while (i < 5)
    {
        cli[i] = accept(socket_desc, (struct sockaddr *)&client[i], (socklen_t *)&c);
        cout << "Conn Accepted" << endl;
        pthread_create(&threadid[i], NULL, connection_handler, (void *)&cli[i]);
        i++;
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    return 0;
}