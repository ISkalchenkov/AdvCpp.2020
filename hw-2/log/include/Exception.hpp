#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

namespace log {

class LoggerError : public std::exception {
public:
    explicit LoggerError(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message_;
};

} // namespace log

#endif // EXCEPTION_HPP
