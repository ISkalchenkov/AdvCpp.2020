#include "FileDescriptor.hpp"
#include "Exception.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <utility>
#include <iostream>

namespace epoll_server {

FileDescriptor::FileDescriptor() : fd_(-1) {
}

FileDescriptor::FileDescriptor(int fd)
    : fd_(fd) {
}

FileDescriptor::FileDescriptor(FileDescriptor&& rhs) noexcept
    : fd_(std::exchange(rhs.fd_, -1)) {
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor &&rhs) {
    if (&rhs == this) {
        return *this;
    }
    std::swap(fd_, rhs.fd_);
    rhs.close();

    return *this;
}

FileDescriptor& FileDescriptor::operator=(int fd) {
    close();
    fd_ = fd;
}

FileDescriptor::~FileDescriptor() noexcept {
    try {
        close();
    } catch (const CloseError& err) {
        std::cerr << err.what() << std::endl;
    }
}

int FileDescriptor::get_fd() const {
    return fd_;
}

void FileDescriptor::set_fd(int fd) {
    close();
    fd_ = fd;
}

int FileDescriptor::extract() {
    return std::exchange(fd_, -1);
}

bool FileDescriptor::is_opened() const {
    return fd_ >= 0;
}

void FileDescriptor::close() {
    if (fd_ < 0) {
        return;
    }
    if (::close(fd_) < 0) {
        fd_ = -1;
        throw CloseError("Error closing socket: ");
    }
    fd_ = -1;
}

} // namespace epoll_server
