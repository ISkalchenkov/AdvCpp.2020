//
// Created by antarctica on 13.03.2020.
//

#include "Process.h"

namespace proc {

Process::Process(const std::string &path) :is_readable(true) {
    if (pipe(p2c_pipefd) == -1) {
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }
    if (pipe(c2p_pipefd) == -1) {
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (dup2(p2c_pipefd[0], STDIN_FILENO) == -1) {
            perror("Dup error");
            exit(EXIT_FAILURE);
        }
        if (dup2(c2p_pipefd[1], STDOUT_FILENO) == -1) {
            perror("Dup error");
            exit(EXIT_FAILURE);
        }
        ::close(p2c_pipefd[0]);
        ::close(p2c_pipefd[1]);
        ::close(c2p_pipefd[0]);
        ::close(c2p_pipefd[1]);
        if (execl(path.c_str(), path.c_str(), nullptr) == -1) {
            perror("Execl error");
            exit(EXIT_FAILURE);
        }
    } else {
        ::close(p2c_pipefd[0]);
        ::close(c2p_pipefd[1]);
    }
}

Process::~Process() {
    close();
    if (kill(pid, SIGTERM) == -1) {
        perror("Kill error");
    }
    if (waitpid(pid, nullptr, 0) == -1) {
        perror("Waitpid error");
    }
}

bool Process::isReadable() const {
    return is_readable;
}

size_t Process::write(const void *data, size_t len) {
    ssize_t bytes_written = ::write(p2c_pipefd[1], data, len);
    if (bytes_written == -1) {
        perror("Write error");
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
    ssize_t bytes_read = ::read(c2p_pipefd[0], data, len);
    if (bytes_read == -1) {
        perror("Read error");
    } else if (bytes_read == 0)
        is_readable = false;
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
    ::close(p2c_pipefd[1]);
}

void Process::close() {
    ::close(p2c_pipefd[1]);
    ::close(c2p_pipefd[0]);
    is_readable = false;
}

} // proc

