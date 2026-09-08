#include "ServerSocket.hpp"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>

ServerSocket::ServerSocket(int domain, int socketType, int protocol, int port, u_long interface)
    : BaseSocket(domain, socketType, protocol, port, interface) {
  attachSocketToAddress();
  listenForConnection(10);
}

void ServerSocket::attachSocketToAddress() {
  struct sockaddr *addressPtr = (struct sockaddr *)&address;
  int bindingResult = bind(socketFileDecriptor, addressPtr, sizeof(address));
  if (bindingResult == -1) {
    std::cerr << "\033[31mFailed to bind socket to the port: " << port << std::endl;
    std::cerr << "Message: " << std::strerror(errno) << std::endl;
    std::cerr << "error(" << errno << ")\033[0m" << std::endl;

    std::string message = "Failed to binding socket to port\n";
    throw std::runtime_error(message);
  }
}

void ServerSocket::listenForConnection(int maxConn) {
  int listenResult = listen(socketFileDecriptor, maxConn);
  if (listenResult == -1) {
    std::cerr << "\033[31mFailed to listen for conncetion on socket: " << socketFileDecriptor
              << std::endl;
    std::cerr << "Message: " << std::strerror(errno) << std::endl;
    std::cerr << "error(" << errno << ")\033[0m" << std::endl;

    std::string message = "Failed to listem for conncetion\n";
    throw std::runtime_error(message);
  }
}