#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>

#include "err.h"
#include "defs.h"
#include "example-data.h"

#define BUFFER_SIZE   2000
#define QUEUE_LENGTH     5

class MyStream {
    int &port;
public:
    MyStream(int &msg_sock) : port(msg_sock) {}

    void operator>>(const std::string &s) {
        const char *c = s.c_str();
        unsigned long messageLength = s.length();
        ssize_t status = write(port, c, s.length());
        if (status != messageLength)
            syserr("Writing to socket");
    }
};

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Wrong number of arguments\n");
        printf("Usage: %s [port_number]\n", argv[0]);
        return -1;
    }
    int sock, msg_sock, portNum = atoi(argv[1]);

    socklen_t client_address_len;

    char buffer[BUFFER_SIZE];
    ssize_t len, snd_len;

    MyStream istr(msg_sock);

    sock = socket(PF_INET, SOCK_STREAM, 0); // creating IPv4 TCP socket
    if (sock < 0)
        syserr("socket");
    // after socket() call; we should close(sock) on any execution path;
    // since all execution paths exit immediately, sock would be closed when program terminates

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_address.sin_family = AF_INET; // IPv4
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // listening on all interfaces
    server_address.sin_port = htons(portNum); // listening on port portNum

    // bind the socket to a concrete address
    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        syserr("bind");

    // switch to listening (passive open)
    if (listen(sock, QUEUE_LENGTH) < 0)
        syserr("listen");

    printf("accepting client connections on port %hu\n", ntohs(server_address.sin_port));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    for (;;) {
        client_address_len = sizeof(client_address);
        // get client connection from the socket
        msg_sock = accept(sock, (struct sockaddr *) &client_address, &client_address_len);
        if (msg_sock < 0)
            syserr("accept");

        printf("new socket connection with return status %d accepted\n", msg_sock);

        //telnet negotiations
        istr >> tnet::DEFAULT_NEGOTIATION_MESSAGE;

        istr >> ansi::CLEAR_SCREEN + ansi::SUPRESS_LOCAL_ECHO;
        exampleData hud;

        do {
            //TODO make screen refresh conditional
            istr >> ansi::RESET_CURSOR + ansi::CLEAR_SCREEN;
            istr >> hud.getContent();
            len = read(msg_sock, buffer, sizeof(buffer));
            if (len < 0)
                syserr("reading from client socket");
            else {
                printf("read from socket: %zd bytes: %.*s\n(", len, (int) len, buffer);
                for (int i = 0; i < len; ++i) {
                    printf("%hhu ", buffer[i]);
                }
                printf(")\n");
                // TODO handle input
            }
        } while (len > 0);
        printf("ending connection\n");
        if (close(msg_sock) < 0)
            syserr("close");
    }
#pragma clang diagnostic pop

    return 0;
}
