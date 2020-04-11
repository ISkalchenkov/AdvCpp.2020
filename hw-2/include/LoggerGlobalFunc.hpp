#ifndef LOGGER_GLOBAL_FUNC_HPP
#define LOGGER_GLOBAL_FUNC_HPP

#include "Logger.hpp"

namespace log {

void debug(const std::string& msg);
void info(const std::string& msg);
void warn(const std::string& msg);
void error(const std::string& msg);

BaseLoggerPtr create_file_logger(const std::string& path, Level lvl);
BaseLoggerPtr create_stdout_logger(Level lvl);
BaseLoggerPtr create_stderr_logger(Level lvl);

} // namespace log

#endif // LOGGER_GLOBAL_FUNC_HPP
