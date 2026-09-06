#ifndef BASE_SOCKET
#define BASE_SOCKET

#include <netinet/in.h>
#include <sys/socket.h>

class BaseSocket {
protected:
  int socketFileDecriptor;
  struct sockaddr_in address;

public:
  BaseSocket(int domain, int socketType, int protocol, int port, u_long interface);

  ~BaseSocket();

  virtual void attachSocketToAddress() = 0;
};

#endif
