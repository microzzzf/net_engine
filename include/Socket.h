#ifndef SOCKET_OPS_H_
#define SOCKET_OPS_H_

namespace netengine
{

class Socket
{
public:
    int create();
    void bind(const int socket_fd, const struct sockaddr* addr);
    void listen(const int socket_fd);
    int accept(const int socket_fd);
    ssize_t send(const int socket_fd, char* buffer, int len);
    ssize_t receive(const int socket_fd, char* buffer, int len);

private:
};

}

#endif
