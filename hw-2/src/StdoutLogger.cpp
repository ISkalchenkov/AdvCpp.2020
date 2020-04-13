#include <iostream>

#include "StdoutLogger.hpp"
#include "LogModifier.hpp"

namespace log {

StdoutLogger::StdoutLogger(Level lvl) noexcept: BaseLogger(lvl) {
}

void StdoutLogger::flush() noexcept {
    std::cout.flush();
}

void StdoutLogger::log(const std::string &msg, Level lvl) noexcept {
    if (lvl >= level()) {
        std::cout << LogModifier::get_instance().formate(msg, lvl) << std::endl;
    }
}

} // namespace log
