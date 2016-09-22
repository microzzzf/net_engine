/*************************************************************************
	> File Name: TcpClient.cpp
	> Author: Fan Zhang
	> Mail: zhangfan41792@163.com
	> Created Time: 2016年09月22日 星期四 22时15分56秒
 ************************************************************************/

#include "TcpClient.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <signal.h>

using namespace std;

int connected = 1;

void reset(int)
{
    connected = 0;
}

void TcpClient::create()
{
    int client_fd = 0;

    while(1)
    {
        if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            cout<<strerror(errno)<<endl;
            exit(1);
        }

        const int PORT = 3333;
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if(connect(client_fd, (struct sockaddr*)(&server_addr), sizeof(server_addr)) < 0)
        {
            cout<<strerror(errno)<<endl;
            exit(1);
        }

        const int BUFFER_LEN = 4096;
        char send_buffer[BUFFER_LEN];
        char rec_buffer[BUFFER_LEN];
        connected = 1;

        while(fgets(send_buffer, sizeof(send_buffer), stdin) != NULL && connected)
        {
            send(client_fd, send_buffer, strlen(send_buffer), 0);
            signal(SIGPIPE, reset);
            recv(client_fd, rec_buffer, sizeof(rec_buffer), 0);
            cout<<rec_buffer;

            memset(send_buffer, 0, sizeof(send_buffer));
            memset(rec_buffer, 0, sizeof(rec_buffer));
        }
        close(client_fd);
    }   
}
