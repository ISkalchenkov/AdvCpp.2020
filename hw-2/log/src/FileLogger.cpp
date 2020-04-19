#include <memory>

#include "FileLogger.hpp"

namespace log {

FileLogger::FileLogger() noexcept : file_out_("default.log") {
}

FileLogger::FileLogger(const std::string& file_path, Level lvl) noexcept
    : file_out_(file_path)
    , BaseLogger(lvl) {
}

FileLogger::FileLogger(const std::string &file_path, Level lvl, const LogModifier& mod) noexcept
    : file_out_(file_path)
    , BaseLogger(lvl, mod){
}

void FileLogger::flush() noexcept {
    file_out_.flush();
}

void FileLogger::log(const std::string &msg, Level lvl) noexcept {
    if (lvl >= level()) {
        file_out_ << mod_.format(msg, lvl) << std::endl;
    }
}

} // namespace log
