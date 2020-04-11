#include "Logger.hpp"
#include "LoggerGlobalFunc.hpp"

int main() {
    log::debug("Debug");
    log::info("Info");
    log::warn("Warn");
    log::error("Error");
    return 0;
}
