#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <thread>
#include "TcpServer.h"

using namespace std;

int connected = 1;

void reset(int)
{
    connected = 0;
}

int createSocket(int socket_fd)
{
    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cout<<strerror(errno)<<endl;
        exit(1);
    }

    struct sockaddr_in my_addr;
    const int PORT = 3333;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 8);

    // when the server process exit without client closing the socket, should reuse the socket.
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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

    return socket_fd;
}

void newService(int socket_fd)
{
    //int socket_fd = *((int*)fd);
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

void TcpServer::create()
{
    //pthread_t tid[2];

    int socket_fd = 0;
    socket_fd = createSocket(socket_fd);

    //pthread_create(&tid[0], NULL, newService, (void*)(&socket_fd));
    //pthread_create(&tid[0], NULL, newService, (void*)(&socket_fd));
    
    thread my_thread;
    my_thread = thread(newService, socket_fd);

    while(1)
    {
    }
}
