#include "Connection.hpp"
#include "Exception.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <utility>
#include <cstring>
#include <sys/epoll.h>

namespace epoll_server {

Connection::Connection(const std::string& address, uint16_t port) {
    connect(address, port);
}

Connection::Connection(int fd, int epoll_fd, const sockaddr_in& client_addr)
        : socket_(fd)
        , epoll_fd_(epoll_fd)
        , dst_port_(ntohs(client_addr.sin_port))
        , dst_addr_(inet_ntoa(client_addr.sin_addr)) {
}

Connection::Connection(Connection&& rhs) noexcept
    : socket_(std::move(rhs.socket_))
    , dst_addr_(std::move(rhs.dst_addr_))
    , dst_port_(std::exchange(rhs.dst_port_, 0)) {
}

Connection& Connection::operator=(Connection &&rhs) noexcept {
    if (&rhs == this) {
        return *this;
    }
    socket_ = std::move(rhs.socket_);
    dst_addr_ = std::move(rhs.dst_addr_);
    dst_port_ = std::exchange(rhs.dst_port_, 0);

    return *this;
}

int Connection::create_socket() {
    int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (fd < 0)
        throw SocketError("Error creating socket: ");
    return fd;
}

void Connection::connect(const std::string& address, uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_aton(address.c_str(), &addr.sin_addr) == 0) {
        throw AddressError("Error parsing IP address, ip = " + address);
    }

    FileDescriptor tmp(create_socket());
    if (::connect(tmp.get_fd(), reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw SocketError("Connection error: ");
    }

    socket_ = std::move(tmp);

    dst_addr_ = address;
    dst_port_ = port;
}


void Connection::close() {
    socket_.close();
}

size_t Connection::input_data_length() const {
    return input_data_.length();
}

const std::string& Connection::get_input_data() const {
    return input_data_;
}

bool Connection::is_opened() const {
    return socket_.is_opened();
}

size_t Connection::write(const void *data, size_t len) {
    while (true) {
        ssize_t bytes_written = ::write(socket_.get_fd(), data, len);
        if (bytes_written == -1) {
            if (errno == EINTR)
                continue;
            if (errno == EWOULDBLOCK || errno == EAGAIN)
                return 0;
            throw WriteError("Write error: ");
        }
        return bytes_written;
    }
}

void Connection::writeExact(const void *data, size_t len) {
    ssize_t total_bytes_written = 0;
    const char *begin = static_cast<const char *>(data);
    while (total_bytes_written != len) {
        ssize_t bytes_written = write(begin, len - total_bytes_written);
        if (!bytes_written) {
            throw ConnectionError("Total bytes written: "
                + std::to_string(total_bytes_written) + ". Not available to write exactly");
        }
        total_bytes_written += bytes_written;
        begin += bytes_written;
    }
}

size_t Connection::read(void *data, size_t len) {
    while (true) {
        ssize_t bytes_read = ::read(socket_.get_fd(), data, len);
        if (bytes_read == -1) {
            if (errno == EINTR)
                continue;
            if(errno == EWOULDBLOCK || errno == EAGAIN)
                return 0;
            throw ReadError("Read error: ");
        } else if (bytes_read == 0) {
            close();
            throw ConnectionError("Connection closed");
        }
        input_data_ += std::string(static_cast<const char*>(data), bytes_read);
        return bytes_read;
    }
}

void Connection::readExact(void *data, size_t len) {
    ssize_t total_bytes_read = 0;
    char *begin = static_cast<char *>(data);
    while (total_bytes_read != len) {
        ssize_t bytes_read{};
        try {
            bytes_read = read(begin, len - total_bytes_read);
        } catch (const ConnectionError& err) {
            throw ConnectionError("Total bytes read: "
                + std::to_string(total_bytes_read) + ". Connection closed");
        }

        if (!bytes_read) {
            throw ConnectionError("Total bytes read: "
                + std::to_string(total_bytes_read) + ". Not available to read exactly");
        }
        begin += bytes_read;
        total_bytes_read += bytes_read;
    }
}

uint16_t Connection::get_dst_port() const {
    return dst_port_;
}

const std::string& Connection::get_dst_addr() const {
    return dst_addr_;
}

void Connection::set_event(uint32_t event) {
    event_ = event;
}

uint32_t Connection::get_event() const {
    return event_;
}

void Connection::modify_epoll(uint32_t events) {
    epoll_event event{};
    event.data.fd = socket_.get_fd();
    event.events = events;
    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, socket_.get_fd(), &event) < 0) {
        throw EpollError("Epoll_ctl error: ");
    }
}

} // namespace epoll_server
