#ifndef LOGGER_H
#define LOGGER_H

#include <memory>

#include "BaseLogger.hpp"

namespace log {

using BaseLoggerPtr = std::unique_ptr<BaseLogger>;

class Logger {
public:
    static Logger& get_instance() noexcept;

    BaseLogger& get_global_logger() const noexcept;
    void set_global_logger(BaseLoggerPtr logger) noexcept;

    Logger(const Logger& rhs) = delete;
    Logger& operator=(const Logger& rhs) = delete;
    Logger(Logger&& rhs) = delete;
    Logger& operator=(Logger&& rhs) = delete;

private:
    BaseLoggerPtr global_logger_;

    Logger();
    ~Logger() = default;

};

} // namespace log

#endif // LOGGER_H
