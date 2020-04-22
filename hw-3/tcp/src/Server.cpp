#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Exception.hpp"
#include "Server.hpp"

namespace tcp {

Server::Server(const std::string& address, uint16_t port, int max_connect)
    : is_opened_(true) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_aton(address.c_str(), &addr.sin_addr) == 0) {
        throw AddressError("Error parsing address: invalid IP address");
    }

    if (bind(socket_.get_fd(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        throw SocketError("Socket binding error: ");
    }

    set_max_connect(max_connect);
}

Server::Server(Server&& rhs) noexcept
    : socket_(std::move(rhs.socket_))
    , is_opened_(rhs.is_opened_) {
    rhs.is_opened_ = false;
}

Server& Server::operator=(Server &&rhs) noexcept {
    if (&rhs == this) {
        return *this;
    }
    socket_ = std::move(rhs.socket_);
    is_opened_ = rhs.is_opened_;
    rhs.is_opened_ = false;
    return *this;
}

Server::~Server() noexcept {
    close();
}


void Server::open(const std::string& address, uint16_t port, int max_connect) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_aton(address.c_str(), &addr.sin_addr) == 0) {
        throw AddressError("Error parsing address: invalid IP address");
    }

    Socket socket_tmp;
    if (bind(socket_.get_fd(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        throw SocketError("Socket binding error: ");
    }

    socket_ = std::move(socket_tmp);

    set_max_connect(max_connect);
}

void Server::set_max_connect(int max_connect) {
    if (listen(socket_.get_fd(), max_connect) < 0) {
        throw SocketError("Socket listen error: ");
    }
}

Connection Server::accept() {
    sockaddr_in client_addr{};
    socklen_t addr_size = sizeof(client_addr);

    int fd = ::accept(socket_.get_fd(), reinterpret_cast<sockaddr*>(&client_addr), &addr_size);
    if (fd < 0) {
        throw SocketError("Socket accept error: ");
    }
    return Connection(fd, client_addr);
}


bool Server::is_opened() const {
    return is_opened_;
}

void Server::close() {
    if (is_opened_) {
        socket_.close();
        is_opened_ = false;
    }
}

} // namespace tcp