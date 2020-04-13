#include "Logger.hpp"
#include "LoggerGlobalFunc.hpp"

int main() {
    std::string log_path = "logger.log";
    log::init(log::create_file_logger(log_path, log::Level::DEBUG));

    log::debug("debug message");
    log::info("info message");
    log::warn("warn message");
    log::error("error message");

    log::init(log::create_stdout_logger(log::Level::DEBUG));
    log::set_all_mod(log::Modification::ON);

    log::debug("debug message");
    log::info("info message");
    log::warn("warn message");
    log::error("error message");

    log::set_weight_mod(log::Modification::OFF);
    log::init(log::create_stderr_logger(log::Level::DEBUG));

    log::debug("debug message");
    log::info("info message");
    log::warn("warn message");
    log::error("error message");

    return 0;
}
