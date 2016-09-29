#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "Socket.h"

namespace netengine
{

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    void newConnection();

private:
    void newSubThreadForConnection();

    static const int PORT = 3333;
    static const int BACKLOG = 10;
    static const int LEN_BUFFER = 4096;

    Socket* m_socket;
};

}



#endif
