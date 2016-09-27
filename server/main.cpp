#include <iostream>
#include "TcpServer.h"

using namespace netengine;

int main(int argc, char* argv[])
{
    TcpServer server;
    server.newConnection();
    
    return 0;
}
