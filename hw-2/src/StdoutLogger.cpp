#include <iostream>

#include "StdoutLogger.hpp"

namespace log {

StdoutLogger::StdoutLogger(Level lvl) noexcept: BaseLogger(lvl) {
}

void StdoutLogger::flush() noexcept {
    std::cout.flush();
}

void StdoutLogger::log(const std::string &msg, Level lvl) noexcept {
    if (lvl >= level()) {
        std::cout << msg << std::endl;
    }
}

} // namespace log
