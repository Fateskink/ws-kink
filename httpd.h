#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define LISTENADDR "0.0.0.0"

/* global */
char *error;

// return 0 on error, or return socket
int srv_init(int portno) {
  int s;
  struct sockaddr_in srv;

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    error = "socket() error";

    return 0;
  }

  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = inet_addr(LISTENADDR);
  srv.sin_port = htons(portno);

  if (bind(s, (struct sockaddr *)&srv, sizeof(srv))) {
    close(s);
    error = "bind() error";

    return 0;
  }

  if (listen(s, 5)) {
    close(s);
    error  = "listen() error";

    return 0;
  }

  return s;
}

// return 0 on error or return the new client's socket fd
int cli_accept(int s) {
  int c;
  socklen_t addrlen;
  struct sockaddr_in cli;

  addrlen = 0;
  memset(&cli, 0, sizeof(cli));
  c = accept(s, (struct sockaddr *)&cli, &addrlen);
  if (c < 0) {
    error = "accept() error";

    return 0;
  }

  return c;
}

int cli_connect(int s, int c) {
  return 0;
}
