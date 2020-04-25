//
// Created by antarctica on 13.03.2020.
//

#include "Process.h"
#include "Exception.h"

#include <iostream>

int main() {
        std::string path = "./echo";
        std::string hello = "Hello world!";
        std::string buf(hello.size(),'\0');
    try {
        proc::Process process(path);
        process.writeExact(hello.c_str(), hello.size());
        process.closeStdin();
        process.readExact(buf.data(), hello.size());
        process.close();
    }
    catch (const proc::ProcessError& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    std::cout << buf << std::endl;

    return 0;
}
