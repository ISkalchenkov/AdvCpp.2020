#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <semaphore.h>

namespace shmem {

class Semaphore {
public:
    Semaphore(bool shared, unsigned int value);
    ~Semaphore() noexcept;

    Semaphore(const Semaphore& rhs) = delete;
    Semaphore& operator=(const Semaphore& rhs) = delete;

    void lock();
    void unlock();

    void destroy();

private:
    sem_t semaphore_;
};


class SemaphoreLock {
public:
    explicit SemaphoreLock(Semaphore& sem);
    ~SemaphoreLock() noexcept;

private:
    Semaphore& sem_;
};

} // namespace shmem

#endif // SEMAPHORE_HPP
