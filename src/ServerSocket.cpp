#include "ServerSocket.hpp"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>

ServerSocket::ServerSocket(int domain, int socketType, int protocol, int port, u_long interface)
    : BaseSocket(domain, socketType, protocol, port, interface) {
  attachSocketToAddress();
}

void ServerSocket::attachSocketToAddress() {
  int bindingResult = bind(socketFileDecriptor, (struct sockaddr *)&address, sizeof(address));
  if (bindingResult == -1) {
    std::cerr << "Failed to bind socket to the port: " << port << std::endl;
    std::cerr << "Message: " << std::strerror(errno) << std::endl;
    std::cerr << "error(" << errno << ")" << std::endl;

    std::string message = "Failed to binding socket to port";
    throw std::runtime_error(message);
  }
}
