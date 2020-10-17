#include "Exception.hpp"

#include <cstring>

namespace shmem {

SemaphoreError::SemaphoreError(const std::string& msg)
    : std::runtime_error(msg + strerror(errno)) {
}

ShmemError::ShmemError(const std::string& msg)
    : std::runtime_error(msg + strerror(errno)) {
}

} // namespace shmem