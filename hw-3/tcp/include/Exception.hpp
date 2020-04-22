#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

namespace tcp {

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

class ReadError : public BasicException {
public:
    explicit ReadError(const std::string& message);
};

class WriteError : public BasicException {
public:
    explicit WriteError(const std::string& message);
};

class EofError : public BasicException {
public:
    explicit EofError(const std::string& message);
};

} // namespace tcp

#endif // EXCEPTION_HPP
