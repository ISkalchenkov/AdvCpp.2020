set(EPOLL_SERVER_LIB_SRCS
        "src/Connection.cpp"
        "src/Server.cpp"
        "src/Exception.cpp"
        "src/FileDescriptor.cpp"
)

add_library(${EPOLL_SERVER_LIB_NAME} STATIC ${EPOLL_SERVER_LIB_SRCS})
target_include_directories(${EPOLL_SERVER_LIB_NAME} PUBLIC include)
