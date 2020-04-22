#include "StdoutLogger.hpp"
#include "Logger.hpp"
#include "Exception.hpp"

namespace log {

Logger::Logger() : global_logger_(std::make_unique<StdoutLogger>()) {
}

Logger& Logger::get_instance() noexcept {
    static Logger instance;
    return instance;
}

BaseLogger& Logger::get_global_logger() const noexcept {
    return *global_logger_;
}

void Logger::set_global_logger(BaseLoggerPtr logger) {
    if (logger) {
        global_logger_ = std::move(logger);
    } else {
        throw LoggerError("Pointer setting error: NULL pointer passed");
    }
}

} // namespace log
