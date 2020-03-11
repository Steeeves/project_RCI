#ifndef HEADER_FILE
#define HEADER_FILE

struct Server {
  int fd;
  int newfd;
  int errcode;
  ssize_t n;
  socklen_t addrlen;
  struct addrinfo hints;
  struct addrinfo *res;
  struct sockaddr_in addr;
  char buffer[128];
};

struct Server init_udp_sv();
struct Server listen_udp_sv(struct Server);
void close_udp_sv(struct Server);

struct Server init_tcp_sv();
struct Server listen_tcp_sv(struct Server);
void close_tcp_sv(struct Server);


#endif
