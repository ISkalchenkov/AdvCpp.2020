#include <stdexcept>
#include <cstring>

#include "Exception.hpp"

namespace tcp {

BasicException::BasicException(const std::string& message)
    :message_(message) {
}

const char * BasicException::what() const noexcept {
    return message_.c_str();
}

SocketError::SocketError(const std::string& message)
    : BasicException(message + strerror(errno)) {
}

AddressError::AddressError(const std::string& message)
    : BasicException(message) {
}

ReadError::ReadError(const std::string& message)
    : BasicException(message + strerror(errno)) {
}

WriteError::WriteError(const std::string& message)
        : BasicException(message + strerror(errno)) {
}

EofError::EofError(const std::string& message)
        : BasicException(message) {
}

} // namespace tcp
