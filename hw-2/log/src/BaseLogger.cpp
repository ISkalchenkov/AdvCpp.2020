#include "BaseLogger.hpp"

namespace log {

BaseLogger::BaseLogger() noexcept : level_(Level::INFO) {
}

BaseLogger::BaseLogger(Level lvl) noexcept : level_(lvl) {
}

BaseLogger::BaseLogger(log::Level lvl, const LogModifier& mod) noexcept
    : level_(lvl)
    , mod_(mod) {
}

void BaseLogger::debug(const std::string &msg) {
    log(msg, Level::DEBUG);
}

void BaseLogger::info(const std::string &msg) {
    log(msg, Level::INFO);
}

void BaseLogger::warn(const std::string &msg) {
    log(msg, Level::WARN);
}

void BaseLogger::error(const std::string &msg) {
    log(msg, Level::ERROR);
}

void BaseLogger::set_level(Level lvl) {
    level_ = lvl;
}

Level BaseLogger::level() const {
    return level_;
}

} // namespace log
