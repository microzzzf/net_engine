#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace netengine
{

class Socket
{
public:
    Socket();
    ~Socket();
    void bind(const int socket_fd, const struct ::sockaddr* addr) const;
    void listen(const int socket_fd) const;
    int accept(const int socket_fd) const;
    ssize_t send(const int socket_fd, char* buffer, int len) const;
    ssize_t receive(const int socket_fd, char* buffer, int len) const;

    int getSocketFd();

private:
    int m_socket_fd;
};

}

#endif
