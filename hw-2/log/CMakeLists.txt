cmake_minimum_required(VERSION 3.15)

set(LOG_LIB_SRCS
        "src/BaseLogger.cpp"
        "src/StdoutLogger.cpp"
        "src/StderrLogger.cpp"
        "src/FileLogger.cpp"
        "src/Logger.cpp"
        "src/LoggerGlobalFunc.cpp"
        "src/LogModifier.cpp"
        "src/Exception.cpp"
)

add_library(${LOG_LIB_NAME} STATIC ${LOG_LIB_SRCS})
target_include_directories(${LOG_LIB_NAME} PUBLIC include)
