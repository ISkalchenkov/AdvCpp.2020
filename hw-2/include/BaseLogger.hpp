#ifndef BASE_LOGGER_H
#define BASE_LOGGER_H

#include <string>

namespace log {

enum class Level {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class BaseLogger {
public:
    BaseLogger() noexcept;
    explicit BaseLogger(Level lvl) noexcept;
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
};

} // namespace log

#endif // BASE_LOGGER_H
