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

class socketstream {
    constexpr static int BUFFER_SIZE = 2000;
    static char buffer[BUFFER_SIZE];
    int port;

public:
    socketstream(int sock, struct sockaddr_in &client_address, socklen_t &client_address_len);

    ~socketstream();

    /// read from socket connection
    void operator>>(std::__cxx11::string &s);

    /// write to socket connection
    void operator<<(const std::__cxx11::string &s);
};

#endif //INC_1_SOCKETSTREAM_H
