#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <fstream>

#include "BaseLogger.hpp"

namespace log {

class FileLogger : public BaseLogger {
public:
    FileLogger() noexcept;
    explicit FileLogger(const std::string& file_path, Level lvl) noexcept;

    FileLogger(const FileLogger& rhs) = delete;
    FileLogger& operator=(const FileLogger& rhs) = delete;

    FileLogger(FileLogger&& rhs) = delete;
    FileLogger& operator=(FileLogger&& rhs) = delete;

    void flush() noexcept override;

private:
    std::ofstream file_out_;

    void log(const std::string& msg, Level lvl) noexcept override;
};

} // namespace log

#endif // FILE_LOGGER_H