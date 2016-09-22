#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <vector>
#include <pthread.h>

using namespace std;

class TcpServer
{
public:
    void create();

private:
    vector<int> m_socket_fds;
};

#endif
