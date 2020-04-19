#include "Logger.hpp"
#include "LoggerGlobalFunc.hpp"

int main() {

    std::string log_path = "logger.log";

    log::LogModifier mod;
    mod.set_time_mod(log::Modification::ON);
    log::init(log::create_file_logger(log_path, log::Level::DEBUG, mod));

    log::debug("debug message");
    log::info("info message");
    log::warn("warn message");
    log::error("error message");

    mod.set_all_mod(log::Modification::ON);
    log::init(log::create_stdout_logger(log::Level::DEBUG, mod));

    log::debug("debug message");
    log::info("info message");
    log::warn("warn message");
    log::error("error message");

    mod.set_all_mod(log::Modification::OFF);
    log::init(log::create_stderr_logger(log::Level::DEBUG, mod));

    log::debug("debug message");
    log::info("info message");
    log::warn("warn message");
    log::error("error message");

    return 0;
}
