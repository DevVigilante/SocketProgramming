#include "BaseSocket.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

BaseSocket::BaseSocket(int domain, int socketType, int protocol, int port, u_long interface) {
  this->port = port;

  std::cout << "Creating socket for port: " << port << std::endl;

  socketFileDecriptor = socket(domain, socketType, protocol);

  address.sin_family = domain;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = htonl(interface);

  if (socketFileDecriptor < 0) {
    std::cout << "Failed to create socket\nport: " << port << "\nDesciptor: " << socketFileDecriptor
              << std::endl;
  }

  std::cout << "Socket created " << socketFileDecriptor << std::endl;
}

BaseSocket::~BaseSocket() { close(socketFileDecriptor); }
