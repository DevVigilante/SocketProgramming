#ifndef BASE_SOCKET
#define BASE_SOCKET

#include <netinet/in.h>
#include <sys/socket.h>

class BaseSocket {
protected:
  int socketFileDecriptor;
  int port;
  struct sockaddr_in address;
  virtual void attachSocketToAddress() = 0;

public:
  BaseSocket(int domain, int socketType, int protocol, int port, u_long interface);

  ~BaseSocket();

  int getPort();
};

#endif
