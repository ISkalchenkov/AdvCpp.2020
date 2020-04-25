#include "Connection.hpp"
#include "Exception.hpp"

#include <iostream>

int main() {
    std::string ip = "127.0.0.1";
    uint16_t port = 11111;
    int message_size = 256;

    try {
        tcp::Connection connection(ip, port);

        connection.set_send_timeout(5);
        connection.set_receive_timeout(5);

        std::string message(message_size, '\0');
        std::string buf(message_size, '\0');
        std::cout << "Connected" << std::endl;
        std::cout << "Enter your message: ";
        std::cin.getline(message.data(), message.size());

        connection.writeExact(message.c_str(), message_size);
        std::cout << "Sent: " << message << std::endl;
        connection.readExact(buf.data(), message_size);
        std::cout << "Received: " << buf << std::endl;

    }
    catch (const tcp::BasicException& err) {
        std::cerr << err.what() << std::endl;
    }
}
