#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "server_test.h"

#define PORT "58001"

struct Server init_udp_sv(void){

  struct Server server;

  server.fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server.fd == -1) /**error*/ exit(1);

  memset (&server.hints, 0, sizeof server.hints);
  server.hints.ai_family = AF_INET;
  server.hints.ai_socktype = SOCK_DGRAM;
  server.hints.ai_flags = AI_PASSIVE;

  server.errcode = getaddrinfo(NULL, PORT, &server.hints, &server.res);
  if (server.errcode != 0) /*error*/  exit(1);

  server.n = bind(server.fd, server.res->ai_addr, server.res->ai_addrlen);
  if(server.n == -1) /*error*/ exit(-1);

  return server;
}

struct Server listen_udp_sv(struct Server server){

  while(1){

    server.addrlen = sizeof(server.addr);

    server.n = recvfrom(server.fd, server.buffer, 128, 0, (struct sockaddr*) &server.addr, &server.addrlen);
    if (server.n==-1) /*error*/ exit(1);
    write(1, "received: ", 9);
    write(1, server.buffer, server.n);

    server.n = sendto(server.fd, server.buffer, server.n, 0, (struct sockaddr*) &server.addr, server.addrlen);
    if (server.n==-1) /*error*/ exit(1);
  }

  freeaddrinfo(server.res);
  close(server.fd);

  return server;
}

int main(void){
  struct Server server = init_udp_sv();
  server = listen_udp_sv(server);
}
