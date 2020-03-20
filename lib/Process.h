//
// Created by antarctica on 17.03.2020.
//

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

namespace proc{

class Process {
public:
    explicit Process(const std::string& path);
    ~Process();
    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);
    bool isReadable() const;
    void closeStdin();
    void close();

private:
    int p2c_pipefd[2];
    int c2p_pipefd[2];
    bool is_readable;
    pid_t pid;

};

} // proc

#endif //PROCESS_H
