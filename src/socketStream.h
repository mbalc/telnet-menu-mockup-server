#ifndef INC_1_SOCKETSTREAM_H
#define INC_1_SOCKETSTREAM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include "err.h"
#include "example-data.h"

class socketStream {
    constexpr static int BUFFER_SIZE = 2000;
    static char buffer[BUFFER_SIZE];
    int port;

public:
    /// get client connection from the socket
    socketStream(int sock, struct sockaddr_in &client_address, socklen_t &client_address_len);

    /// close opened connection
    ~socketStream();

    /// read from socket connection
    void operator>>(std::__cxx11::string &s);

    /// write to socket connection
    void operator<<(const std::__cxx11::string &s);
};

#endif //INC_1_SOCKETSTREAM_H
