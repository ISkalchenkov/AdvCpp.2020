#ifndef STDOUT_LOGGER_H
#define STDOUT_LOGGER_H

#include "BaseLogger.hpp"

namespace log {

class StdoutLogger : public BaseLogger {
public:
    StdoutLogger() = default;
    explicit StdoutLogger(Level lvl) noexcept;

    StdoutLogger(const StdoutLogger& rhs) = delete;
    StdoutLogger& operator=(const StdoutLogger& rhs) = delete;

    StdoutLogger(StdoutLogger&& rhs) = delete;
    StdoutLogger&& operator=(StdoutLogger&& rhs) = delete;

    void flush() noexcept override;

private:
    void log(const std::string& msg, Level lvl) noexcept override;
};

} // namespace log

#endif // STDOUT_LOGGER_H
