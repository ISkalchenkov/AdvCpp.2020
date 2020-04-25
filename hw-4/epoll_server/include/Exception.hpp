#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

namespace epoll_server {

class BasicException : public std::exception {
public:
    explicit BasicException(const std::string& message);
    virtual ~BasicException() noexcept = default;

    const char* what() const noexcept override;

private:
    std::string message_;
};

class SocketError : public BasicException {
public:
    explicit SocketError(const std::string& message);
};

class AddressError : public BasicException {
public:
    explicit AddressError(const std::string& message);
};

} // namespace epoll_server

#endif // EXCEPTION_HPP
