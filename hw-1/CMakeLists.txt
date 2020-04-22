cmake_minimum_required(VERSION 3.15)
project(dz1)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
add_library(process src/Process.cpp)
add_library(descriptor src/Descriptor.cpp)

add_executable(dz1 src/main.cpp)
target_link_libraries(dz1 process descriptor)

add_executable(echo examples/echo.cpp)


