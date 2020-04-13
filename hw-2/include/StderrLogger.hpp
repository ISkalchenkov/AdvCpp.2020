#ifndef STDERR_LOGGER_H
#define STDERR_LOGGER_H

#include "BaseLogger.hpp"

namespace log {

class StderrLogger: public BaseLogger {
public:
    StderrLogger() = default;
    explicit StderrLogger(Level lvl) noexcept;

    StderrLogger(const StderrLogger& rhs) = delete;
    StderrLogger& operator=(const StderrLogger& rhs) = delete;

    StderrLogger(StderrLogger&& rhs) = delete;
    StderrLogger&& operator=(StderrLogger&& rhs) = delete;

    void flush() noexcept override;

private:
    void log(const std::string& msg, Level lvl) noexcept override;
};

} // namespace log

#endif // STDERR_LOGGER_H
