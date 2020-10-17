cmake_minimum_required(VERSION 3.15)
project(epoll_server)

set(CMAKE_CXX_STANDARD 20)

set(EPOLL_SERVER_LIB_NAME "epoll_server")

add_subdirectory(examples)
add_subdirectory(epoll_server)
