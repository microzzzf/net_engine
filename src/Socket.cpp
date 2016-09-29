#include "Socket.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace netengine;

Socket::Socket()
{
    m_socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    
    if(m_socket_fd < 0)
    {
        std::cout<<::strerror(errno)<<std::endl;
    }
}

Socket::~Socket()
{
    close(m_socket_fd);
}

void Socket::bind(const int socket_fd, const struct ::sockaddr* addr) const
{
    if(::bind(socket_fd, addr, sizeof(::sockaddr)) < 0)
    {
        std::cout<<::strerror(errno)<<std::endl;
    }
}

void Socket::listen(const int socket_fd) const
{
    if(::listen(socket_fd, SOMAXCONN) < 0)
    {
        std::cout<<::strerror(errno)<<std::endl;
    }
}

int Socket::accept(const int socket_fd) const
{
    int another_fd = 0;
    ::sockaddr_in remote_addr;
    int sin_size = sizeof(::sockaddr_in);

    another_fd = ::accept(socket_fd, (::sockaddr*)(&remote_addr), (socklen_t*)&sin_size);

    if(another_fd < 0)
    {
        std::cout<<strerror(errno)<<std::endl;
    }

    return another_fd;
}

ssize_t Socket::send(const int socket_fd, char* buffer, int len) const
{
    return ::send(socket_fd, buffer, len, 0);
}
    
ssize_t Socket::receive(const int socket_fd, char* buffer, int len) const
{
    return ::recv(socket_fd, buffer, len, 0);
}

int Socket::getSocketFd()
{
    return m_socket_fd;
}
