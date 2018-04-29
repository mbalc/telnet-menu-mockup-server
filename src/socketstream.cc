#include "socketstream.h"

char socketstream::buffer[socketstream::BUFFER_SIZE];

socketstream::socketstream(int sock, struct sockaddr_in &client_address, socklen_t &client_address_len)
        : port(accept(sock, (struct sockaddr *) &client_address, &client_address_len)) {
    if (port < 0)
        syserr("accept");

    printf("new client connection with return status %d accepted\n", port);
}

socketstream::~socketstream() {
    printf("ending connection\n");
    if (close(port) < 0)
        syserr("close");
}

void socketstream::operator>>(std::__cxx11::string &s) {
    ssize_t len = read(port, buffer, sizeof(buffer));
    if (len < 0)
        syserr("reading from client socket");
    s = std::__cxx11::string(buffer, len);
}

void socketstream::operator<<(const std::__cxx11::string &s) {
    const char *c = s.c_str();
    unsigned long messageLength = s.length();
    ssize_t status = write(port, c, s.length());
    if (status != messageLength)
        syserr("Writing to socket");
}
