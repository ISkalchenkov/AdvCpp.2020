#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>
#include <stdexcept>

namespace shmem {

class SemaphoreError : public std::runtime_error {
public:
    explicit SemaphoreError(const std::string& msg);
};

class ShmemError : public std::runtime_error {
public:
    explicit ShmemError(const std::string& msg);
};

} // namespace shmem

#endif // EXCEPTION_HPP
