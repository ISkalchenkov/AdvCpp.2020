//
// Created by antarctica on 30.03.2020.
//

#ifndef DZ1_DESCRIPTOR_H
#define DZ1_DESCRIPTOR_H

#include <memory>

namespace proc {
    class Descriptor {
    public:
        Descriptor() noexcept;
        explicit Descriptor(const int fd) noexcept;
        Descriptor(const Descriptor& rhs) = delete;
        Descriptor( Descriptor&& rhs) noexcept;
        ~Descriptor() noexcept;
        Descriptor& operator=(const Descriptor& rhs) = delete;
        Descriptor& operator=(Descriptor&& rhs);

        void close() noexcept;
        int getFd() const noexcept;
        void setFd(const int fd) noexcept;
        bool isOpened() const noexcept;
    private:
        struct FdData {
            FdData();
            FdData(const int fd);
            int fd_;
            bool is_opened_;
        };
        std::unique_ptr<FdData> fd_data_;

    };
} // proc

#endif //DZ1_DESCRIPTOR_H
