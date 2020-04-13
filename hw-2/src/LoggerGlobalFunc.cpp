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

void init(BaseLoggerPtr logger) {
    Logger::get_instance().set_global_logger(std::move(logger));
}

void set_color_mod(Modification mod) {
    LogModifier::get_instance().set_color_mod(mod);
}

void set_weight_mod(Modification mod) {
    LogModifier::get_instance().set_weight_mod(mod);
}

void set_time_mod(Modification mod) {
    LogModifier::get_instance().set_time_mod(mod);
}

void set_all_mod(Modification mod) {
    LogModifier::get_instance().set_all_mod(mod);
}

} // namespace log
