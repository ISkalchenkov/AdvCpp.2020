#include "FileLogger.hpp"
#include "LogModifier.hpp"

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
        file_out_ << LogModifier::get_instance().formate(msg, lvl) << std::endl;
    }
}

} // namespace log
