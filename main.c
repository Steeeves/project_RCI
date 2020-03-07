#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#include "server_test.h"

int max(int, int);

int main(){
  struct Server udp_server = init_udp_sv();
  struct Server tcp_server = init_tcp_sv();
  fd_set rfds;
  enum {idle, busy} state;
  int maxfd, counter;

  state=idle;
  while(1){
    FD_ZERO(&rfds);
    FD_SET(udp_server.fd, &rfds);
    FD_SET(tcp_server.fd, &rfds);
    maxfd = max(udp_server.fd, tcp_server.fd) + 1;

    counter = select(maxfd, &rfds, (fd_set*)NULL, (fd_set*)NULL, (struct timeval *)NULL);

    if(counter <= 0) /*error*/
      exit(1);

    if(FD_ISSET(udp_server.fd, &rfds)){
      udp_server = listen_udp_sv(udp_server);
    }

    if(FD_ISSET(tcp_server.fd, &rfds)){
      tcp_server = listen_tcp_sv(tcp_server);
    }
  }
  close_tcp_sv(tcp_server);
  close_udp_sv(udp_server);
}

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
