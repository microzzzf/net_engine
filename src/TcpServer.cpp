#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
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

TcpServer::~TcpServer()
{
    delete m_socket;
}

void TcpServer::newSubThreadForConnection()
{
    int socket_fd = m_socket->getSocketFd();

    int client_fd = 0;
    char buffer[LEN_BUFFER];

    while(1)
    {
        client_fd = m_socket->accept(socket_fd);

        connected = 1;
        while(connected)
        {
            m_socket->receive(client_fd, buffer, sizeof(buffer));
            std::cout<<buffer;
            memset(buffer, 0, sizeof(buffer));
            memcpy(buffer, "done\n", 5);
            m_socket->send(client_fd, buffer, strlen(buffer));
            signal(SIGPIPE, reset);
            memset(buffer, 0, sizeof(buffer));
        }

        close(client_fd);
    }
}

TcpServer::TcpServer()
{
    m_socket = new Socket();
    const int socket_fd = m_socket->getSocketFd();
    
    struct ::sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 8);

    m_socket->bind(socket_fd, (struct ::sockaddr*)(&my_addr));
    m_socket->listen(socket_fd);
}

void TcpServer::newConnection()
{
    std::thread th[2];
    th[0] = std::thread(std::bind(&TcpServer::newSubThreadForConnection, this));
    th[1] = std::thread(std::bind(&TcpServer::newSubThreadForConnection, this));

    while(1)
    {
    }
}
