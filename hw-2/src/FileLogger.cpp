#include "FileLogger.hpp"

namespace log {

FileLogger::FileLogger() noexcept : file_out_("default.log"){
}

FileLogger::FileLogger(const std::string &file_path, Level lvl) noexcept
    : file_out_(file_path), BaseLogger(lvl) {
}

void FileLogger::flush() noexcept {
    file_out_.flush();
}

void FileLogger::log(const std::string &msg, Level lvl) noexcept {
    if (lvl >= level()) {
        file_out_ << msg << std::endl;
    }
}

} // namespace log
