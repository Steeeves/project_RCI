#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#include "server_test.h"

struct Server init_tcp_sv(char* gate){

  struct Server server;

  server.fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server.fd == -1) /**error*/ exit(1);

  memset(&server.hints, 0, sizeof server.hints);
  server.hints.ai_family = AF_INET;
  server.hints.ai_socktype = SOCK_STREAM;
  server.hints.ai_flags = AI_PASSIVE;

  server.errcode = getaddrinfo(NULL, gate, &server.hints, &server.res);
  if (server.errcode != 0) /*error*/  exit(1);

  server.n = bind(server.fd, server.res->ai_addr, server.res->ai_addrlen);
  if(server.n == -1) /*error*/ exit(-1);

  if (listen(server.fd,5) == -1) /*error*/ exit(1);

  return server;
}

struct Server listen_tcp_sv(struct Server server){

  server.addrlen = sizeof(server.addr);
  if((server.newfd = accept(server.fd, (struct sockaddr*) &server.addr,
        &server.addrlen)) == -1) /*error*/ exit(1);

  server.n = read(server.newfd, server.buffer, 128);
  if (server.n==-1) /*error*/ exit(1);
  write(1, "received: ", 10);
  write(1, server.buffer, server.n);

  server.n = write(server.newfd, server.buffer, server.n);
  if (server.n==-1) /*error*/ exit(1);

  close(server.newfd);

  return server;
}

void close_tcp_sv(struct Server server){
  freeaddrinfo(server.res);
  close(server.fd);
}

struct Server init_udp_sv(char* gate){

  struct Server server;

  server.fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server.fd == -1) /**error*/ exit(1);

  memset(&server.hints, 0, sizeof server.hints);
  server.hints.ai_family = AF_INET;
  server.hints.ai_socktype = SOCK_DGRAM;
  server.hints.ai_flags = AI_PASSIVE;

  server.errcode = getaddrinfo(NULL, gate, &server.hints, &server.res);
  if (server.errcode != 0) /*error*/  exit(1);

  server.n = bind(server.fd, server.res->ai_addr, server.res->ai_addrlen);
  if(server.n == -1) /*error*/ exit(-1);

  return server;
}

struct Server listen_udp_sv(struct Server server){

  server.addrlen = sizeof(server.addr);

  server.n = recvfrom(server.fd, server.buffer, 128, 0, (struct sockaddr*) &server.addr, &server.addrlen);
  if (server.n==-1) /*error*/ exit(1);
  write(1, "received: ", 9);
  write(1, server.buffer, server.n);

  server.n = sendto(server.fd, server.buffer, server.n, 0, (struct sockaddr*) &server.addr, server.addrlen);
  if (server.n==-1) /*error*/ exit(1);

  return server;
}

void close_udp_sv(struct Server server){
  freeaddrinfo(server.res);
  close(server.fd);
}

/*
int main(void){
  struct Server udp_server = init_udp_sv();
  struct Server tcp_server = init_tcp_sv();
  udp_server = listen_udp_sv(udp_server);
  tcp_server = listen_tcp_sv(tcp_server);
}
*/
