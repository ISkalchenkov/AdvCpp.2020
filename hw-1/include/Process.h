//
// Created by antarctica on 17.03.2020.
//

#ifndef PROCESS_H
#define PROCESS_H

#include "Descriptor.h"

#include <string>

namespace proc {

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
    Descriptor read_fd_;
    Descriptor write_fd_;
    bool is_readable_;
    pid_t pid_;

};

} // proc

#endif //PROCESS_H
