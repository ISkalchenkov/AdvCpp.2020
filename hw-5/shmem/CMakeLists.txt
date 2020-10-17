set(SHMEM_LIB_SRCS
        "src/Semaphore.cpp"
        "src/Exception.cpp"
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(${SHMEM_LIB_NAME} STATIC ${SHMEM_LIB_SRCS})
target_link_libraries(${SHMEM_LIB_NAME} Threads::Threads)
target_include_directories(${SHMEM_LIB_NAME} PUBLIC include)

