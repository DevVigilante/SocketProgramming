#ifndef SERVER_SOCKET
#define SERVER_SOCKET

#include "BaseSocket.hpp"

class ServerSocket : public BaseSocket {

public:
  ServerSocket(int domain, int socketType, int protocol, int port, u_long interface);

  void attachSocketToAddress();
  void listenForConnection(int maxConnection);
};

#endif
