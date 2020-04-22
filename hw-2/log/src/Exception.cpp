#include "Exception.hpp"

namespace log {

LoggerError::LoggerError(const std::string& message)
    : message_(message) {
}

const char *LoggerError::what() const noexcept {
    return message_.c_str();
}

} // namespace log
