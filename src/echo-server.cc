#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "err.h"
#include "defs.h"
#include "example-data.h"
#include "socketStream.h"

#define QUEUE_LENGTH    20

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        printf("Usage: %s [port_number]\n", argv[0]);
        return 1;
    }
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    std::string input;
    std::string const *output;

    socklen_t client_address_len;
    int portNum = atoi(argv[1]);
    int sock = socket(PF_INET, SOCK_STREAM, 0); // creating IPv4 TCP socket
    if (sock < 0)
        syserr("socket");
    // after socket() call; we should close(sock) on any execution path;
    // since all execution paths exit immediately, sock would be closed when program terminates


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
        socketStream istr(sock, client_address, client_address_len);
        output = &outs::EMPTY;
        exampleData hud(input, output);


        //telnet negotiations
        istr << tnet::DEFAULT_NEGOTIATION_MESSAGE;

        istr << ansi::CLEAR_SCREEN + ansi::SUPRESS_LOCAL_ECHO;

        do {
            istr << ansi::RESET_CURSOR + ansi::CLEAR_SCREEN;
            istr << hud.getContent() + ansi::FONT_BOLD + *output + ansi::FONT_RESET + ansi::ENTER;
            istr >> input;
            if (input == keys::ARROW_UP) hud.move(-1);
            if (input == keys::ARROW_DOWN) hud.move(1);
            if (input == keys::ENTER) hud.execute();
        } while (input.length() > 0);
    }
#pragma clang diagnostic pop

    return 0;
}
