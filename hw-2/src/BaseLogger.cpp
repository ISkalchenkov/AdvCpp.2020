#include "BaseLogger.hpp"

namespace log {

BaseLogger::BaseLogger() noexcept : level_(Level::INFO) {
}

BaseLogger::BaseLogger(log::Level lvl) noexcept : level_(lvl) {
}

void BaseLogger::debug(const std::string &msg) noexcept {
    log(msg, Level::DEBUG);
}

void BaseLogger::info(const std::string &msg) noexcept {
    log(msg, Level::INFO);
}

void BaseLogger::warn(const std::string &msg) noexcept {
    log(msg, Level::WARN);
}

void BaseLogger::error(const std::string &msg) noexcept {
    log(msg, Level::ERROR);
}

void BaseLogger::set_level(Level lvl) noexcept {
    level_ = lvl;
}

Level BaseLogger::level() const noexcept {
    return level_;
}

} // namespace log
