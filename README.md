# net_engine
a TCP/IP server&amp;client engine based on socket


TODO:


1.code refactoring.


2.problem that "address already in use" when the server process exit with "Ctrl+c".

    (done) : add function "setsockopt" before binding.


3.several sockets on one port.

    (done) : create, bind and listen in main thread with socket_fd, accept, send&recv in sub threads with client_fd.

    socket_fd is used for listening and client_fd is used for send/recv, so the best way is to use the same socket_fd to listen rather than different socket_fd in different threads to listen so we can use the same port for different client connections.


4.how to connect again when the server process exit and client process does not exit.
    
    (done) need to modifiy the client program. 
    
    4.1. not good enough : handle with signal SIGPIPE. But it will miss three messages while re-connect to the server.
    
    4.2. the better way is to design a guard process of heart beat on client side to verify whether the server process is still alive.
