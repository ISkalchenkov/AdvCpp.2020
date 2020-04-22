cmake_minimum_required(VERSION 3.15)

set(TCP_LIB_SRCS
        "src/Connection.cpp"
        "src/Server.cpp"
        "src/Exception.cpp"
        "src/Socket.cpp"
)

add_library(${TCP_LIB_NAME} STATIC ${TCP_LIB_SRCS})
target_include_directories(${TCP_LIB_NAME} PUBLIC include)
