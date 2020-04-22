#ifndef STDOUT_LOGGER_H
#define STDOUT_LOGGER_H

#include "BaseLogger.hpp"

namespace log {

class StdoutLogger : public BaseLogger {
public:
    StdoutLogger() = default;
    explicit StdoutLogger(Level lvl) noexcept;
    explicit StdoutLogger(Level lvl, const LogModifier& mod) noexcept;

    void flush() override;

private:
    void log(const std::string& msg, Level lvl) override;
};

} // namespace log

#endif // STDOUT_LOGGER_H
