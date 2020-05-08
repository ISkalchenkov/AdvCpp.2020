#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <new>

namespace shmem {

struct AllocState {
    char* start;
    char* end;
};

template <class T>
class Allocator {
public:
    using value_type = T;

public:
    explicit Allocator(AllocState* state) : state_(state) {
    }

    template<class S>
    explicit Allocator(const Allocator<S>& rhs) : state_(rhs.get_state()) {
    }

    T* allocate(size_t n) {
        char* result = state_->start;
        if (state_->start + sizeof(T) * n > state_->end)
            throw std::bad_alloc();
        state_->start += sizeof(T) * n;
        return reinterpret_cast<T*>(result);
    }

    void deallocate(T* ptr, size_t n) {
        if (state_->start - sizeof(T) * n == reinterpret_cast<char *>(ptr)) {
            state_->start -= sizeof(T) * n;
        }
    }

    [[nodiscard]] AllocState* get_state() const {
        return state_;
    }

private:
    AllocState* state_;
};

} // namespace shmem

#endif // ALLOCATOR_HPP
