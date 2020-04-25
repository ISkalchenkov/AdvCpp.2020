cmake_minimum_required(VERSION 3.15)
project(dz1)

set(CMAKE_CXX_STANDARD 20)

add_library(process STATIC src/Process.cpp src/Descriptor.cpp)
target_include_directories(process PUBLIC include)

add_executable(dz1 examples/main.cpp)
target_link_libraries(dz1 process)

add_executable(echo examples/echo.cpp)


