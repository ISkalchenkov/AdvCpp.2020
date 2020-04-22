#include "Socket.hpp"
#include "Exception.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <utility>
#include <iostream>

namespace tcp {

Socket::Socket() {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0) {
        throw SocketError("Error creating socket: ");
    }
}

Socket::Socket(int fd)
    : fd_(fd) {
}

Socket::Socket(Socket&& rhs) noexcept
    : fd_(std::exchange(rhs.fd_, -1)) {
}

Socket& Socket::operator=(Socket &&rhs) noexcept {
    if (&rhs == this) {
        return *this;
    }
    this->close();
    this->fd_ = std::exchange(rhs.fd_, -1);

    return *this;
}

Socket::~Socket() noexcept {
    try {
        close();
    } catch (const SocketError& err) {
        std::cerr << err.what() << std::endl;
    }
}

int Socket::get_fd() const {
    return fd_;
}

bool Socket::is_opened() const {
    return fd_ >= 0;
}

void Socket::open() {
    close();
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0) {
        throw SocketError("Error creating socket: ");
    }
}

void Socket::close() {
    if (fd_ < 0) {
        return;
    }
    if (::close(fd_) < 0) {
        throw SocketError("Error closing socket: ");
    }
    fd_ = -1;
}

} // namespace tcp
