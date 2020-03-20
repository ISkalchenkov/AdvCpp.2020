#include "Process.h"
#include <string.h>

int main() {
    std::string path = "./echo";
    std::string hello = "Hello world!";
    char buf[100];
    memset(buf, '\0', sizeof(buf));

    proc::Process process(path);
    process.write(hello.c_str(), hello.size());
    process.closeStdin();
    process.readExact(buf, hello.size());
    process.close();

    std::cout << buf << std::endl;

    return 0;
}
