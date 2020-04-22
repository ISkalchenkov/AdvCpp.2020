#include "Connection.hpp"
#include "Exception.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace tcp {

Connection::Connection(const std::string& address, uint16_t port)
    : is_opened_(true)
    , dst_addr_(address)
    , dst_port_(port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_aton(address.c_str(), &addr.sin_addr) == 0) {
        throw AddressError("Error parsing address: invalid IP address");
    }
    if (::connect(socket_.get_fd(), reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw SocketError("Connection error: ");
    }
}

Connection::Connection(Connection&& rhs) noexcept
    : socket_(std::move(rhs.socket_))
    , dst_addr_(std::move(rhs.dst_addr_))
    , dst_port_(rhs.dst_port_)
    , is_opened_(rhs.is_opened_) {
    rhs.is_opened_ = false;
}

Connection& Connection::operator=(Connection &&rhs) noexcept {
    if (&rhs == this) {
        return *this;
    }
    socket_ = std::move(rhs.socket_);
    dst_addr_ = std::move(rhs.dst_addr_);
    dst_port_ = rhs.dst_port_;
    is_opened_ = rhs.is_opened_;
    rhs.is_opened_ = false;

    return *this;
}

Connection::~Connection() noexcept {
    close();
}

void Connection::connect(const std::string& address, uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_aton(address.c_str(), &addr.sin_addr) == 0) {
        throw AddressError("Error parsing address: invalid IP address");
    }

    Socket socket_tmp;
    if (::connect(socket_tmp.get_fd(), reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw SocketError("Connection error: ");
    }

    socket_ = std::move(socket_tmp);

    dst_addr_ = address;
    dst_port_ = port;
    is_opened_ = true;
}

Connection::Connection(int fd, sockaddr_in client_addr)
    : socket_(fd)
    , dst_port_(ntohs(client_addr.sin_port))
    , dst_addr_(inet_ntoa(client_addr.sin_addr))
    , is_opened_(true) {
}


void Connection::close() {
    if (is_opened_) {
        socket_.close();
        is_opened_ = false;
    }
}

bool Connection::is_opened() const {
    return is_opened_;
}

size_t Connection::write(const void *data, size_t len) {
    ssize_t bytes_written = ::write(socket_.get_fd(), data, len);
    if (bytes_written == -1) {
        throw SocketError("Write error: ");
    }
    return bytes_written;
}

void Connection::writeExact(const void *data, size_t len) {
    ssize_t bytes_written = 0;
    const char *begin = static_cast<const char *>(data);
    while (bytes_written != len) {
        begin += bytes_written;
        bytes_written += write(begin, len - bytes_written);
    }
}

size_t Connection::read(void *data, size_t len) {
    ssize_t bytes_read = ::read(socket_.get_fd(), data, len);
    if (bytes_read == -1) {
        throw SocketError("Read error: ");
    } else if (bytes_read == 0) {
        is_opened_ = false;
    }
    return bytes_read;
}

void Connection::readExact(void *data, size_t len) {
    ssize_t bytes_read = 0;
    char *begin = static_cast<char *>(data);
    while (bytes_read != len) {
        begin += bytes_read;
        bytes_read = read(begin, len - bytes_read);
    }
}

void Connection::set_send_timeout(int sec) {
    timeval timeout{.tv_sec = sec, .tv_usec = 0};
    if (setsockopt(socket_.get_fd(),
            SOL_SOCKET,
            SO_SNDTIMEO,
            &timeout,
            sizeof(timeout)) < 0) {
        throw SocketError("Error setting send timeout: ");
    }
}

void Connection::set_receive_timeout(int sec) {
    timeval timeout{.tv_sec = sec, .tv_usec = 0};
    if (setsockopt(socket_.get_fd(),
                   SOL_SOCKET,
                   SO_RCVTIMEO,
                   &timeout,
                   sizeof(timeout)) < 0) {
        throw SocketError("Error setting receive timeout: ");
    }
}


uint16_t Connection::get_dst_port() const {
    return dst_port_;
}

const std::string& Connection::get_dst_addr() const {
    return dst_addr_;
}

} // namespace tcp
