#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

namespace tcp {

class SocketError : public std::exception {
public:
    SocketError();
    explicit SocketError(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message_;
};

class AddressError : public std::exception  {
public:
    explicit AddressError(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message_;
};

} // namespace tcp

#endif // EXCEPTION_HPP
