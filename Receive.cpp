#include "Server.hpp"

std::string Server::ft_recv(int socket) {
  ssize_t recv_size = 0;
  std::string recv_msg;
  while (true) {
    memset(msg_, 0, MAX_BUFSIZE);
    recv_size = recv(socket, msg_, MAX_BUFSIZE, 0);
    std::cout << "recv ret: " << recv_size << std::endl;
    if (recv_size < 0) {
      perror("recv failed");
      return "";
    }
    if (recv_size == 0) {
      std::cout << "client send EOF(recv)..." << std::endl;
      Server::disconnectClient(socket);
      connect_msg_.clear();
      return "";
    }
    connect_msg_ += std::string(msg_, recv_size);
    std::cout << "result: " << connect_msg_ << std::endl;
    if (connect_msg_.size() >= 2 && connect_msg_.substr(connect_msg_.size() - 2) == "\r\n") {
      connect_msg_.erase(connect_msg_.size() - 2);
      std::cout << "recv CRLF: " << recv_size << " " << connect_msg_ << std::endl;
      recv_msg = connect_msg_;
      connect_msg_.clear();
      return recv_msg;
    }
  }
}
