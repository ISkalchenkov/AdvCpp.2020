#include <iostream>

#include "StderrLogger.hpp"

namespace log {

StderrLogger::StderrLogger(Level lvl) noexcept
    : BaseLogger(lvl) {
}

StderrLogger::StderrLogger(Level lvl, const LogModifier& mod) noexcept
    : BaseLogger(lvl, mod) {
}

void StderrLogger::flush() {
    std::cerr.flush();
}

void StderrLogger::log(const std::string &msg, Level lvl) {
    if (lvl >= level()) {
        std::cerr << mod_.format(msg, lvl) << std::endl;
    }
}

} // namespace log
