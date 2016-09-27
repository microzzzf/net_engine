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
#include "Socket.h"

using namespace netengine;

int connected = 1;

void reset(int)
{
    connected = 0;
}

int TcpServer::generateSocket()
{
    int socket_fd = 0;

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout<<strerror(errno)<<std::endl;
        return -1;
    }

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 8);

    // when the server process exit without client closing the socket, should reuse the socket.
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(::bind(socket_fd, (struct sockaddr*)(&my_addr), sizeof(sockaddr)) == -1)
    {
        std::cout<<strerror(errno)<<std::endl;
        return -1;
    }

    if(listen(socket_fd, BACKLOG) == -1)
    {
        std::cout<<strerror(errno)<<std::endl;
        return -1;
    }

    return socket_fd;
}

void TcpServer::generateService()
{
    socklen_t sin_size = sizeof(struct sockaddr_in);
    int client_fd = 0;
    struct sockaddr_in remote_addr;
    char buffer[LEN_BUFFER];

    while(1)
    {
        if((client_fd = accept(m_socket_fd, (sockaddr*)(&remote_addr), &sin_size)) == -1)
        {
            std::cout<<strerror(errno)<<std::endl;
            continue;
        }

        connected = 1;
        while(connected)
        {
            recv(client_fd, buffer, sizeof(buffer), 0);
            std::cout<<buffer;
            memset(buffer, 0, sizeof(buffer));
            memcpy(buffer, "done\n", 5);
            send(client_fd, buffer, strlen(buffer), 0);
            signal(SIGPIPE, reset);
            memset(buffer, 0, sizeof(buffer));
        }

        close(client_fd);
    }
                     
    close(m_socket_fd);
}

TcpServer::TcpServer()
{
    m_socket_fd = generateSocket(); 
    if(m_socket_fd == -1)
    {
        std::cout<<"Generate socket error!"<<std::endl;
    }
}

void TcpServer::newConnection()
{
    std::thread th[2];
    th[0] = std::thread(std::bind(&TcpServer::generateService, this));
    th[1] = std::thread(std::bind(&TcpServer::generateService, this));

    while(1)
    {
    }
}
