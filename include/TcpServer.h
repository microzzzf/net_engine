#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "Socket.h"

namespace netengine
{

class TcpServer
{
public:
    TcpServer() : m_socket(new Socket()) {}
    void newConnection();

private:
    int generateSocket();
    void generateService();

    static const int PORT = 3333;
    static const int BACKLOG = 10;
    static const int LEN_BUFFER = 4096;

    //int m_socket_fd;
    Socket m_socket;
};

}



#endif
