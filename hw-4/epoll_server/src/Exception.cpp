#include <cstring>

#include "Exception.hpp"

namespace epoll_server {

BasicException::BasicException(const std::string& message)
        : message_(message) {
}

const char *BasicException::what() const noexcept {
    return message_.c_str();
}

SocketError::SocketError(const std::string& message)
        : BasicException(message + strerror(errno)) {
}

AddressError::AddressError(const std::string& message)
    : BasicException(message) {
    }
    
} // namespace epoll_server
