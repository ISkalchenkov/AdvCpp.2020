#ifndef MAP_HPP
#define MAP_HPP

#include "Allocator.hpp"
#include "SharedMemory.hpp"
#include "Semaphore.hpp"

#include <map>

namespace shmem {

template <class Key, class T, class Compare = std::less<Key>>
class Map {
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;

    using allocator_type = Allocator<value_type>;
    using shared_map = std::map<key_type, mapped_type, Compare, allocator_type>;

    using string_allocator = Allocator<char>;
    using shared_string = std::basic_string<char, std::char_traits<char>, string_allocator>;

    using iterator = typename shared_map::iterator;
    using const_iterator = typename shared_map::const_iterator;

public:
    explicit Map(size_t map_length)
        : shared_memory_(make_shmem<char>(map_length))
        , semaphore_(nullptr) {

        auto* state = reinterpret_cast<AllocState*>(shared_memory_.get());
        state->start = static_cast<char*>(shared_memory_.get()) + sizeof(AllocState);
        state->end = static_cast<char*>(shared_memory_.get()) + map_length;

        semaphore_ = new(state->start) Semaphore(true, 1);
        state->start = static_cast<char*>(state->start) + sizeof(Semaphore);

        allocator_type map_alloc(state);
        map_ = new(state->start) shared_map{map_alloc};
        state->start = static_cast<char*>(state->start) + sizeof(shared_map);
    }

    void destroy() {
        semaphore_->destroy();
        map_->~map();
    }

    // Iterators

    auto begin() {
        SemaphoreLock lock(*semaphore_);
        return map_->begin();
    }

    auto cbegin() const {
        SemaphoreLock lock(*semaphore_);
        return map_->cbegin();
    }

    auto end() {
        SemaphoreLock lock(*semaphore_);
        return map_->end();
    }

    auto cend() const {
        SemaphoreLock lock(*semaphore_);
        return map_->cend();
    }

    // Access to items

    auto& at(const key_type& key) {
        SemaphoreLock lock(*semaphore_);
        return map_->at(key);
    }

    const auto& at(const Key& key) const {
        SemaphoreLock lock(*semaphore_);
        return map_->at(key);
    }

    auto& operator[](const Key& key) {
        SemaphoreLock lock(*semaphore_);
        return map_->operator[](key);
    }

    auto& operator[](Key&& key) {
        SemaphoreLock lock(*semaphore_);
        return map_->operator[](std::move(key));
    }

    // Modification

    void clear() {
        SemaphoreLock lock(*semaphore_);
        map_->clear();
    }

    auto insert(const value_type& value) {
        SemaphoreLock lock(*semaphore_);
        return map_->insert(value);
    }

    auto insert(iterator hint, const value_type& value) {
        SemaphoreLock lock(*semaphore_);
        return map_->insert(hint, value);
    }

    auto insert(const_iterator hint, const value_type& value) {
        SemaphoreLock lock(*semaphore_);
        return map_->insert(hint, value);
    }

    auto erase(const Key& key) {
        SemaphoreLock lock(*semaphore_);
        return map_->erase(key);
    }

    void erase(iterator position) {
        SemaphoreLock lock(*semaphore_);
        map_->erase(position);
    }

    auto erase(const_iterator position) {
        SemaphoreLock lock(*semaphore_);
        return map_->erase(position);
    }

    void erase(iterator first, iterator last) {
        SemaphoreLock lock(*semaphore_);
        return map_->erase(first, last);
    }

    auto erase(const_iterator first, const_iterator last) {
        SemaphoreLock lock(*semaphore_);
        return map_->erase(first, last);
    }

private:
    ShmemPtr<char> shared_memory_;
    shared_map* map_;
    Semaphore* semaphore_;
};

} // namespace shmem

#endif // MAP_HPP
