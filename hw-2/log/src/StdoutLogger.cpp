#include <iostream>

#include "StdoutLogger.hpp"

namespace log {

StdoutLogger::StdoutLogger(Level lvl) noexcept
    : BaseLogger(lvl) {
}

StdoutLogger::StdoutLogger(Level lvl, const LogModifier& mod) noexcept
    : BaseLogger(lvl, mod) {
}

void StdoutLogger::flush() {
    std::cout.flush();
}

void StdoutLogger::log(const std::string &msg, Level lvl) {
    if (lvl >= level()) {
        std::cout << mod_.format(msg, lvl) << std::endl;
    }
}

} // namespace log
