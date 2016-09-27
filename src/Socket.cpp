#include "SocketOps.h"
#include <sys/socket.h>
#include <errno.h>
#include <string.h>

using namespace netengine;

int Socket::create()
{
    int socket_fd = 0;

    socket_fd = ::socket(AF_NET, SOCK_STREAM, IPPROTO_TCP);
    
    if(::socket_fd < 0)
    {
        std::cout<<::strerror(errno)<<std::endl;
    }

    return socket_fd;
}

void Socket::bind(const int socket_fd, const struct sockaddr* addr)
{
    if(::bind(socket_fd, addr, sizeof(sockaddr)) < 0)
    {
        std::cout<<::strerror(errno)<<std::endl;
    }
}

void Socket::listen(const int socket_fd)
{
    if(::listen(socket_fd, SOMAXCONN) < 0)
    {
        std::cout<<::strerror(errno)<<std::endl;
    }
}

void Socket::accept(const int socket_fd)
{
    int another_fd = 0;
    struct sockaddr_in remote_addr;
    int sin_size = sizeof(sockaddr_in);

    another_fd = ::accept(socket_fd, (sockaddr*)(&remote_addr), &sin_size);

    if(another_fd < 0)
    {
        std::cout<<strerror(errno)<<std::endl;
    }
}

ssize_t Socket::send(const int socket_fd, char* buffer, int len)
{
    return ::send(socket_fd, buffer, len, 0);
}
    
ssize_t Socket::receive(const int socket_fd, char* buffer, int len)
{
    return ::recv(socket, buffer, len, 0);
}

