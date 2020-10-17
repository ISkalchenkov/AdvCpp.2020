#include "Map.hpp"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <wait.h>

constexpr size_t MEMORY_SIZE = 4096;

int main() {

    shmem::Map<int, shmem::string> map(MEMORY_SIZE);
    shmem::string_allocator aloc(map.get_allocator().get_state());

    map.insert({1, {100, '1', aloc}});
    map.insert({2, {100, '2', aloc}});
    map.insert({3, {100, '3', aloc}});

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork error: " << std::strerror(errno) << std::endl;
    }

    if (pid == 0) {
        std::cout << "<Child>" << std::endl;

        auto it = map.begin();
        while (it != map.end()) {
            std::cout << it->first << ' ' << it->second << std::endl;
            it++;
        }
        map.insert({4, {100, '4', aloc}});
        map.insert({5, {100, '5', aloc}});
        map.insert({6, {100, '6', aloc}});

    } else {
        sleep(2);
        std::cout << "<Parent>" << std::endl;
        auto it = map.begin();
        while (it != map.end()) {
            std::cout << it->first << ' ' << it->second << std::endl;
            it++;
        }

        map.destroy();
        kill(pid, SIGTERM);
        waitpid(pid, nullptr, 0);
    }

    return 0;
}
