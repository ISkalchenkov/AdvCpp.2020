#ifndef STDERR_LOGGER_H
#define STDERR_LOGGER_H

#include "BaseLogger.hpp"

namespace log {

class StderrLogger: public BaseLogger {
public:
    StderrLogger() = default;
    explicit StderrLogger(Level lvl) noexcept;
    explicit StderrLogger(Level lvl, const LogModifier& mod) noexcept;

    void flush() noexcept override;

private:
    void log(const std::string& msg, Level lvl) noexcept override;
};

} // namespace log

#endif // STDERR_LOGGER_H
