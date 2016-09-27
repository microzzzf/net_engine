#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

namespace netengine
{

class TcpServer
{
public:
    TcpServer();
    void newConnection();

private:
    int generateSocket();
    void generateService();

    static const int PORT = 3333;
    static const int BACKLOG = 10;
    static const int LEN_BUFFER = 4096;

    int m_socket_fd;
};

}



#endif
