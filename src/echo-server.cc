#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>

#include "err.h"
#include "ansi.h"

#define BUFFER_SIZE   2000
#define QUEUE_LENGTH     5

class MyStream {
    int& port;
public:
    MyStream(int& msg_sock) : port(msg_sock){}

    void operator>> (const std::string &s) {
      const char *c = s.c_str();
      ssize_t status = write(port, c, s.length());
      if (status < 0)
        syserr("Writing to socket");
    }
};

int main(int argc, char *argv[])
{
  int sock, msg_sock;

  if (argc != 2) {
    printf ("Wrong number of arguments\n");
    printf ("Usage: %s [port_number]\n", argv[0]);
    return -1;
  }
  int portNum = atoi(argv[1]);

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
  for (;;) {
    client_address_len = sizeof(client_address);
    // get client connection from the socket
    msg_sock = accept(sock, (struct sockaddr *) &client_address, &client_address_len);
    if (msg_sock < 0)
      syserr("accept");

    printf("new connection on socket slot %d accepted\n", msg_sock);
    write(msg_sock,"\377\375\042\377\375\001",6); //negotiations
    do {
      len = read(msg_sock, buffer, sizeof(buffer));
      istr >> ansi::CLEAR_SCREEN;
      if (len < 0)
        syserr("reading from client socket");
      else {
        printf("read from socket: %zd bytes: %.*s\n", len, (int) len, buffer);
        snd_len = write(msg_sock, buffer, len);
        if (snd_len != len)
          syserr("writing to client socket");
      }
    } while (len > 0);
    printf("ending connection\n");
    if (close(msg_sock) < 0)
      syserr("close");
  }

  return 0;
}
