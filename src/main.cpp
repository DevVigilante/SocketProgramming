#include "ServerSocket.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8000

int main() {

  try {
    ServerSocket mServer(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY);
  } catch (const std::runtime_error &e) {
    std::cerr << "Server thrown runtime error:\n";
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
