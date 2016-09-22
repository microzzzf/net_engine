# net_engine
a TCP/IP server&amp;client engine based on socket

TODO:
1. code refactoring;
2. problem that "address already in use" when the server process exit with "Ctrl+c"
3. several sockets on one port
4. socket_fd is used for listening and client_fd is used for send/recv, so the best way is to use the same socket_fd to listen rather than different socket_fd in different threads to listen so we can use the same port for different client connections.
