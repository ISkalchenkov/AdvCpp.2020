#include "Semaphore.hpp"
#include "Exception.hpp"

#include <iostream>

namespace shmem {

// class Semaphore

Semaphore::Semaphore(bool shared, unsigned int value)
    : semaphore_{} {
    if (sem_init(&semaphore_, static_cast<int>(shared), value) < 0) {
        throw SemaphoreError("Semaphore initialization error: ");
    }
}

Semaphore::~Semaphore() noexcept {
    try {
        destroy();
    } catch (const SemaphoreError& err) {
        std::cerr << err.what() << std::endl;
    }
}

void Semaphore::lock() {
    while (sem_wait(&semaphore_) < 0) {
        if (errno == EINTR)
            continue;
        throw SemaphoreError("Semaphore wait error: ");
    }
}

void Semaphore::unlock() {
    if (sem_post(&semaphore_) < 0) {
        throw SemaphoreError("Semaphore post error: ");
    }
}

void Semaphore::destroy() {
    if (sem_destroy(&semaphore_) < 0) {
        throw SemaphoreError("Semaphore destruction error: ");
    }
}

// class SemaphoreLock

SemaphoreLock::SemaphoreLock(Semaphore& sem)
    : sem_(sem) {
    sem_.lock();
}

SemaphoreLock::~SemaphoreLock() noexcept {
    try {
        sem_.unlock();
    } catch (const SemaphoreError& err) {
        std::cerr << err.what() << std::endl;
    }
}

} // namespace shmem
