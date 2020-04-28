#include <stdexcept>
#include <cstring>

#include "Exception.hpp"

namespace epoll_server {

RuntimeError::RuntimeError(const std::string& message)
    : runtime_error(message) {
}

InvalidArgument::InvalidArgument(const std::string& message)
    : invalid_argument(message) {
}

SocketError::SocketError(const std::string& message)
    : RuntimeError(message + strerror(errno)) {
}

AddressError::AddressError(const std::string& message)
    : InvalidArgument(message) {
}

CloseError::CloseError(const std::string& message)
    : RuntimeError(message + strerror(errno)) {
}

EpollError::EpollError(const std::string& message)
    : RuntimeError(message + strerror(errno)) {
}

ReadError::ReadError(const std::string& message)
    : RuntimeError(message + strerror(errno)) {
}

WriteError::WriteError(const std::string& message)
    : RuntimeError(message + strerror(errno)) {
}

ConnectionError::ConnectionError(const std::string& message)
    : RuntimeError(message) {
}

} // namespace epoll_server
