#include "LogModifier.hpp"

namespace log {

namespace escapeCode {
    const char* RESET = "\x1b[0m";

    const char* BOLD = "\x1b[1m";
    const char* DEFAULT_WEIGHT = "\x1b[22m";

    const char* RED = "\x1b[31m";
    const char* YELLOW = "\x1b[33m";
    const char* BLUE = "\x1b[36m";
    const char* WHITE = "\x1b[37m";
    const char* DEFAULT_COLOR = "\x1b[39m";

} // namespace escapeCode


LogModifier::LogModifier() noexcept
    : weight_(Modification::OFF)
    , color_ (Modification::OFF)
    , time_ (Modification::OFF) {
}

void LogModifier::set_color_mod(Modification mod) {
    color_ = mod;
}

void LogModifier::set_weight_mod(Modification mod) {
    weight_ = mod;
}

void LogModifier::set_time_mod(Modification mod) {
    time_ = mod;
}

void LogModifier::set_all_mod(Modification mod) {
    color_ = mod;
    weight_ = mod;
    time_ = mod;
}

std::string LogModifier::format(const std::string& msg, Level lvl) {
    std::ostringstream fmt_message;
    if (time_ == Modification::ON) {
        time_fmt(fmt_message);
    }

    if (weight_ == Modification::ON) {
        weight_fmt(fmt_message);
    }

    if (color_ == Modification::ON) {
        color_fmt(fmt_message, lvl);
    }

    level_fmt(fmt_message, lvl);
    fmt_message << msg;
    if (color_ == Modification::ON) {
        fmt_message << escapeCode::DEFAULT_COLOR;
    }
    if (weight_ == Modification::ON) {
        fmt_message << escapeCode::DEFAULT_WEIGHT;
    }

    return fmt_message.str();
}

void LogModifier::time_fmt(std::ostringstream &fmt_message) {
    time_t now = time(NULL);
    std::string current_time = ctime(&now);
    current_time.pop_back(); // delete \n
    fmt_message << "[" << current_time << "] : ";
}

void LogModifier::weight_fmt(std::ostringstream &fmt_message) {
    fmt_message << escapeCode::BOLD;
}

void LogModifier::color_fmt(std::ostringstream &fmt_message, Level lvl) {
    switch (lvl) {
        case Level::DEBUG:
            fmt_message << escapeCode::BLUE;
            break;

        case Level::INFO:
            fmt_message << escapeCode::WHITE;
            break;

        case Level::WARN:
            fmt_message << escapeCode::YELLOW;
            break;

        case Level::ERROR:
            fmt_message << escapeCode::RED;
            break;
    }
}

void LogModifier::level_fmt(std::ostringstream &fmt_message, Level lvl) {
    switch (lvl) {
        case Level::DEBUG:
            fmt_message << "DEBUG : ";
            break;

        case Level::INFO:
            fmt_message << "INFO  : ";
            break;

        case Level::WARN:
            fmt_message << "WARN  : ";
            break;

        case Level::ERROR:
            fmt_message << "ERROR : ";
            break;
    }
}

} // namespace log
