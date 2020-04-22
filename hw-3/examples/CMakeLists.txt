cmake_minimum_required(VERSION 3.15)

add_executable(server server.cpp)
target_link_libraries(server ${TCP_LIB_NAME})

add_executable(client client.cpp)
target_link_libraries(client ${TCP_LIB_NAME})
