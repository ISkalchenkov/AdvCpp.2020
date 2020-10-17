cmake_minimum_required(VERSION 3.15)

project(shmem)

set(CMAKE_CXX_STANDARD 20)

set(SHMEM_LIB_NAME "shmem")

add_subdirectory(examples)
add_subdirectory(shmem)