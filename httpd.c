/* httpd.c */
#include "httpd.h"

int main(int argc, char *argv[]) {
  int s, c;
  char *port;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <listening port>\n", argv[0]);

    return -1;
  } else {
    port = argv[1];
  }

  s = srv_init(atoi(port));

  if (!s) {
    fprintf(stderr, "%s\n", error);

    return -1;
  }

  printf("Listening on %s:%s\n", LISTENADDR, port);
  while(1) {
    c = cli_accept(s);
    if (!c) {
      fprintf(stderr, "%s\n", error);
      continue;
    }

    printf("Incomming connection\n");

   if  (!fork()) {
     cli_connect(s, c);
   }
    /*
    for main process: return the nre process id
    for the new process: return 0
    */
  }

  return 0;
}
