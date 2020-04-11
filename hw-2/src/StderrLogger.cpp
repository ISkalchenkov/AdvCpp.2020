#include <iostream>

#include "StderrLogger.hpp"

namespace log {

StderrLogger::StderrLogger(Level lvl) noexcept: BaseLogger(lvl) {
}

void StderrLogger::flush() noexcept {
    std::cerr.flush();
}

void StderrLogger::log(const std::string &msg, Level lvl) noexcept {
    if (lvl >= level()) {
        std::cerr << msg << std::endl;
    }
}

} // namespace log
