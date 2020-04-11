cmake_minimum_required(VERSION 3.15)
project(hw_2)

set(CMAKE_CXX_STANDARD 20)

set(LOG_LIBRARY_SRC src/BaseLogger.cpp src/StdoutLogger.cpp src/StderrLogger.cpp src/FileLogger.cpp
        src/Logger.cpp src/LoggerGlobalFunc.cpp)

include_directories(include)
add_library(logger ${LOG_LIBRARY_SRC})

add_executable(hw_2 examples/logging.cpp)
target_link_libraries(hw_2 logger)
