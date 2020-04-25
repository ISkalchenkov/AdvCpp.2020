#include "Server.hpp"
#include "Exception.hpp"

#include <iostream>
#include <string>

int main() {
    std::string ip = "127.0.0.1";
    uint16_t port = 11111;
    int message_size = 256;
    try {
        tcp::Server server(ip, port);
        tcp::Connection conn(server.accept());

        std::string buf(100, '\0');
        conn.readExact(buf.data(), 256);
        conn.writeExact(buf.c_str(), 256);
    }
    catch (const tcp::BasicException& err) {
        std::cerr << err.what() << std::endl;
    }
}
