#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace epoll_server {

class RuntimeError : public std::runtime_error {
public:
    explicit RuntimeError(const std::string& message);
};

class InvalidArgument : public std::invalid_argument {
public:
    explicit InvalidArgument(const std::string& message);
};

class SocketError : public RuntimeError {
public:
    explicit SocketError(const std::string& message);
};

class AddressError : public InvalidArgument {
public:
    explicit AddressError(const std::string& message);
};

class CloseError : public  RuntimeError {
public:
    explicit CloseError(const std::string& message);
};

class EpollError : public RuntimeError {
public:
    explicit EpollError(const std::string& message);
};

class ReadError : public RuntimeError {
public:
    explicit ReadError(const std::string& message);
};

class WriteError : public RuntimeError {
public:
    explicit WriteError(const std::string& message);
};

class ConnectionError : public RuntimeError {
public:
    explicit ConnectionError(const std::string& message);
};

} // namespace epoll_server

#endif // EXCEPTION_HPP
