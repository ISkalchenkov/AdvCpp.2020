#ifndef BASE_LOGGER_H
#define BASE_LOGGER_H

#include <string>

#include "LogModifier.hpp"
#include "Level.hpp"

namespace log {

class BaseLogger {
public:
    BaseLogger() noexcept;
    explicit BaseLogger(Level lvl) noexcept;
    explicit BaseLogger(Level lvl, const LogModifier& mod) noexcept;
    virtual ~BaseLogger() noexcept = default;

    void debug(const std::string& msg) noexcept;
    void info(const std::string& msg) noexcept;
    void warn(const std::string& msg) noexcept;
    void error(const std::string& msg) noexcept;

    void set_level(Level lvl) noexcept;
    Level level() const noexcept;
    virtual void flush() noexcept = 0;

private:
    virtual void log(const std::string& msg, Level lvl) noexcept = 0;

    Level level_;

protected:
     LogModifier mod_;
};

} // namespace log

#endif // BASE_LOGGER_H
