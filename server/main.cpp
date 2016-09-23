#include <iostream>
#include "TcpServer.h"

using namespace std;

int main(int argc, char* argv[])
{
    TcpServer server;
    server.newConnection();
    
    return 0;
}
