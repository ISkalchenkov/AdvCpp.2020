add_executable(server server.cpp)
target_link_libraries(server ${EPOLL_SERVER_LIB_NAME})

add_executable(client client.cpp)
target_link_libraries(client ${EPOLL_SERVER_LIB_NAME})
