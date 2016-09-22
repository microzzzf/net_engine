#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include "TcpServer.h"

using namespace std;

int connected = 1;

void reset(int)
{
    connected = 0;
}

void* newService(void* port)
{
    int socket_fd = 0;

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cout<<strerror(errno)<<endl;
        exit(1);
    }

    struct sockaddr_in my_addr;
    //const int PORT = 3333;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(*((int*)(port)));
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 8);
    if(bind(socket_fd, (struct sockaddr*)(&my_addr), sizeof(sockaddr)) == -1)
    {
        cout<<strerror(errno)<<endl;
        exit(1);
    }

    const int BACKLOG = 10;
    if(listen(socket_fd, BACKLOG) == -1)
    {
        cout<<strerror(errno)<<endl;
        exit(1);
    }

    socklen_t sin_size;
    int client_fd = 0;
    struct sockaddr_in remote_addr;
    int len = 0;
    sin_size = sizeof(struct sockaddr_in);
    
    const int BUFFER_LEN = 4096;
    char buffer[BUFFER_LEN];

    while(1)
    {
        if((client_fd = accept(socket_fd, (sockaddr*)(&remote_addr), &sin_size)) == -1)
        {
            cout<<strerror(errno)<<endl;
            continue;
        }

        connected = 1;
        while(connected)
        {
            len = recv(client_fd, buffer, sizeof(buffer), 0);
            cout<<buffer;
            memset(buffer, 0, sizeof(buffer));
            memcpy(buffer, "done\n", 5);
            send(client_fd, buffer, strlen(buffer), 0);
            signal(SIGPIPE, reset);
            memset(buffer, 0, sizeof(buffer));
        }

        close(client_fd);
    }
                     
    close(socket_fd);
}

void* test(void*)
{
    cout<<"test"<<endl;
    while(1)
    {
    }
}

void TcpServer::create()
{
    pthread_t tid[2];
    int port1 = 3333;
    int port2 = 4444;

    pthread_create(&tid[0], NULL, newService, (void*)(&port1));
    pthread_create(&tid[1], NULL, newService, (void*)(&port2));
    while(1)
    {
    }
}
