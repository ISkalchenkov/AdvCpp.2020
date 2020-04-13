#include <iostream>

#include "StderrLogger.hpp"
#include "LogModifier.hpp"

namespace log {

StderrLogger::StderrLogger(Level lvl) noexcept: BaseLogger(lvl) {
}

void StderrLogger::flush() noexcept {
    std::cerr.flush();
}

void StderrLogger::log(const std::string &msg, Level lvl) noexcept {
    if (lvl >= level()) {
        std::cerr << LogModifier::get_instance().formate(msg, lvl) << std::endl;
    }
}

} // namespace log
