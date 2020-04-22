//
// Created by antarctica on 30.03.2020.
//

#include "Descriptor.h"

#include <unistd.h>

namespace proc {
    Descriptor::FdData::FdData() :is_opened_(false) {
    }

    Descriptor::FdData::FdData(const int fd) : fd_(fd), is_opened_(true) {
    }

    Descriptor::Descriptor() noexcept : fd_data_(std::make_unique<FdData>()) {
    }

    Descriptor::Descriptor(const int fd) noexcept : fd_data_(std::make_unique<FdData>(fd)) {
    }

    Descriptor::Descriptor( Descriptor&& rhs) noexcept :fd_data_(std::move(rhs.fd_data_)) {
        rhs.fd_data_ = std::make_unique<FdData>();
    }

    Descriptor& Descriptor::operator=(Descriptor&& rhs) {
        if (&rhs == this)
            return *this;
        fd_data_ = std::move(rhs.fd_data_);
        rhs.fd_data_ = std::make_unique<FdData>();
        return *this;
    }

    Descriptor::~Descriptor() noexcept {
            close();
    }

    void Descriptor::close() noexcept {
        if (fd_data_->is_opened_) {
            ::close(fd_data_->fd_);
            fd_data_->is_opened_ = false;
        }
    }

    int Descriptor::getFd() const noexcept {
        if (fd_data_->is_opened_)
            return fd_data_->fd_;
        return -1;
    }
    void Descriptor::setFd(const int fd) noexcept {
        close();
        fd_data_->fd_ = fd;
        fd_data_->is_opened_ = true;
    }

    bool Descriptor::isOpened() const noexcept {
        return fd_data_->is_opened_;
    }
} // proc
