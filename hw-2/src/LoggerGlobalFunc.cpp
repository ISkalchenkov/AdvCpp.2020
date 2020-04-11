#include "LoggerGlobalFunc.hpp"
#include "FileLogger.hpp"
#include "StdoutLogger.hpp"
#include "StderrLogger.hpp"

namespace log {

void debug(const std::string& msg) {
    auto& logger = Logger::get_instance().get_global_logger();
        logger.debug(msg);
}

void info(const std::string& msg) {
    auto& logger = Logger::get_instance().get_global_logger();
    logger.info(msg);
}

void warn(const std::string& msg) {
    auto& logger = Logger::get_instance().get_global_logger();
    logger.warn(msg);
}

void error(const std::string& msg) {
    auto& logger = Logger::get_instance().get_global_logger();
    logger.error(msg);
}

BaseLoggerPtr create_file_logger(const std::string& path, Level lvl) {
    return std::make_unique<FileLogger>(path, lvl);
}

BaseLoggerPtr create_stdout_logger(Level lvl) {
    return std::make_unique<StdoutLogger>(lvl);
}

BaseLoggerPtr create_stderr_logger(Level lvl) {
    return std::make_unique<StderrLogger>(lvl);
}

} // namespace log
