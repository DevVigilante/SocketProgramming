#include "ServerSocket.hpp"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 4096

ServerSocket::ServerSocket(int domain, int socketType, int protocol, int port, u_long interface)
    : BaseSocket(domain, socketType, protocol, port, interface) {
  attachSocketToAddress();
  listenForConnection(10);
  acceptClients();
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

void ServerSocket::acceptClients() {
  int clientSocket = accept(socketFileDecriptor, nullptr, nullptr);

  if (clientSocket == -1) {
    std::cerr << "\033[31mFailed to accept connection\033[0m\n";
    std::cerr << "Message: " << std::strerror(errno) << std::endl;
    std::cerr << "error(" << errno << ")\n";

    return;
  }

  std::cout << "Client connected. Socket: " << clientSocket << std::endl;
  std::string request;
  while (true) {
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead == -1) {
      std::cerr << "Failed to read request of client: " << clientSocket << "\n";
      std::cerr << "Message: " << std::strerror(errno) << std::endl;
      std::cerr << "error(" << errno << ")\n";
      return;
    }

    if (bytesRead == 0) {
      std::cerr << "Client closed connection" << std::endl;
      close(clientSocket);
      return;
    }

    if (bytesRead > 0) {
      if (bytesRead <= MAX_BUFFER_SIZE) {
        buffer[bytesRead] = '\0';
      }
      request.append(buffer, bytesRead);
    }

    if (request.find("\r\n\r\n") != std::string::npos) {
      break;
    }
  }
  std::cout << "Client sent: \n" << request << std::endl;
}