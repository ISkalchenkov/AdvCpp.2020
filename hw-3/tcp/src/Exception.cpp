#include <stdexcept>
#include <cstring>

#include "Exception.hpp"

namespace tcp {

SocketError::SocketError() :message_(strerror(errno)) {
}

SocketError::SocketError(const std::string& message)
    : message_(message + strerror(errno)) {
}

const char * SocketError::what() const noexcept {
    return message_.c_str();
}


AddressError::AddressError(const std::string& message)
    : message_(message) {
}

const char* AddressError::what() const noexcept {
    return message_.c_str();
}

} // namespace tcp