#ifndef SHARED_MEMORY_HPP
#define SHARED_MEMORY_HPP

#include "Exception.hpp"

#include <sys/mman.h>
#include <memory>
#include <functional>

namespace shmem {

template <typename T>
using ShmemPtr = std::unique_ptr<T, std::function<void(T*)>>;

template <typename T>
ShmemPtr<T> make_shmem(size_t n = 1) {
    void* mmap = ::mmap(nullptr, sizeof(T) * n,
                PROT_WRITE | PROT_READ,
                MAP_SHARED | MAP_ANONYMOUS,
                -1, 0);

    if (mmap == MAP_FAILED) {
        throw ShmemError("Error creating mmap: ");
    }

    return {
        reinterpret_cast<T*>(mmap),
        [n](T* t) {
            munmap(t, sizeof(T) * n);
        }
    };
}

} // namespace shmem

#endif // SHARED_MEMORY_HPP
