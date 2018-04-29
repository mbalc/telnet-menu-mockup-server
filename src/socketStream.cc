#include "socketStream.h"

char socketStream::buffer[socketStream::BUFFER_SIZE];

socketStream::socketStream(int sock, struct sockaddr_in &client_address, socklen_t &client_address_len)
        : port(accept(sock, (struct sockaddr *) &client_address, &client_address_len)) {
    if (port < 0)
        syserr("accept");

    printf("new client connection with return status %d accepted\n", port);
}

socketStream::~socketStream() {
    printf("client has disconnected\n");
    if (close(port) < 0)
        syserr("close");
}

void socketStream::operator>>(std::__cxx11::string &s) {
    ssize_t len = read(port, buffer, sizeof(buffer));
    if (len < 0)
        syserr("reading from client socket");
    s = std::__cxx11::string(buffer, len);
}

void socketStream::operator<<(const std::__cxx11::string &s) {
    const char *c = s.c_str();
    unsigned long messageLength = s.length();
    ssize_t status = write(port, c, s.length());
    if (status != messageLength)
        syserr("Writing to socket");
}
