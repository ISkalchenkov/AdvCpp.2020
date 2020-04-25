//
// Created by antarctica on 30.03.2020.
//

#ifndef DZ1_EXCEPTION_H
#define DZ1_EXCEPTION_H

#include <exception>
#include <cstring>

namespace proc {

    class ProcessError : public std::exception {
    public:
        const char* what() const noexcept override {
            return std::strerror(errno);
        }
    };
}
#endif //DZ1_EXCEPTION_H
