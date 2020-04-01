//
// Created by antarctica on 13.03.2020.
//

#include "Process.h"
#include "Exception.h"

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

namespace proc {

Process::Process(const std::string &path) :is_readable_(true) {
    int p2c_fd[2];
    int c2p_fd[2];

    if (pipe(p2c_fd) == -1) {
        throw ProcessError();
    }
    Descriptor p2c_fd_0(p2c_fd[0]);
    Descriptor p2c_fd_1(p2c_fd[1]);
    if (pipe(c2p_fd) == -1) {
        throw ProcessError();
    }
    Descriptor c2p_fd_0(c2p_fd[0]);
    Descriptor c2p_fd_1(c2p_fd[1]);


    pid_ = fork();
    if (pid_ == -1) {
        throw ProcessError();
    } else if (pid_ == 0) {
        if (dup2(p2c_fd_0.getFd(), STDIN_FILENO) == -1) {
            throw ProcessError();
        }
        if (dup2(c2p_fd_1.getFd(), STDOUT_FILENO) == -1) {
            throw ProcessError();
        }

        p2c_fd_0.close();
        p2c_fd_1.close();
        c2p_fd_0.close();
        c2p_fd_1.close();

        if (execl(path.c_str(), path.c_str(), nullptr) == -1) {
            throw ProcessError();
        }
    } else {
        write_fd_ = std::move(p2c_fd_1);
        read_fd_ = std::move(c2p_fd_0);
    }
}

Process::~Process() {
    try {
        close();
    }
    catch (const ProcessError& err)
    {
        std::cerr << err.what() << std::endl;
    }
}

bool Process::isReadable() const {
    return is_readable_;
}

size_t Process::write(const void *data, size_t len) {
    ssize_t bytes_written = ::write(write_fd_.getFd(), data, len);
    if (bytes_written == -1) {
        throw ProcessError();
    }
    return bytes_written;
}

void Process::writeExact(const void *data, size_t len) {
    ssize_t bytes_written = 0;
    const char *begin = static_cast<const char *>(data);
    while (bytes_written != len) {
        begin += bytes_written;
        bytes_written += write(begin, len - bytes_written);
    }
}

size_t Process::read(void *data, size_t len) {
    ssize_t bytes_read = ::read(read_fd_.getFd(), data, len);
    if (bytes_read == -1) {
        throw ProcessError();
    } else if (bytes_read == 0)
        is_readable_ = false;
    return bytes_read;
}

void Process::readExact(void *data, size_t len) {
    ssize_t bytes_read = 0;
    char *begin = static_cast<char *>(data);
    while (bytes_read != len) {
        begin += bytes_read;
        bytes_read = read(begin, len - bytes_read);
    }
}

void Process::closeStdin() {
    write_fd_.close();
}

void Process::close() {
    if (pid_) {
        write_fd_.close();
        read_fd_.close();

        is_readable_ = false;

        if (kill(pid_, SIGTERM) == -1) {
            throw ProcessError();
        }
        if (waitpid(pid_, nullptr, 0) == -1) {
            throw ProcessError();
        }
        pid_ = 0; // child process deleted
    }
}

} // proc
