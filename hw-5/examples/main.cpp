#include "Map.hpp"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <wait.h>

int main() {
    shmem::Map<int, std::string> map(2048);
    map.insert(std::pair<int, std::string>(1, std::string(10, '1')));
    map.insert(std::pair<int, std::string>(2, "222"));
    map.insert(std::pair<int, std::string>(3, "333"));

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork error: " << std::strerror(errno) << std::endl;
    }

    if (pid == 0) {
        map[1][0] = '2';
        std::cout << map[1] << std::endl;
        auto it = map[1].begin();
        int i = 0;
        while (it != map[1].end()) {
            i++;
            it++;
        }
        std::cout << i << std::endl;
        std::cout << map[2] << std::endl;
        std::cout << map[3] << std::endl;
    }
    sleep(5);
    std::cout << map[1] << std::endl;

    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);

    return 0;
}
