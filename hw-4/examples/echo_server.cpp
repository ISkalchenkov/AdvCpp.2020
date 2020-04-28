#include <iostream>
#include <Exception.hpp>

#include "Server.hpp"

constexpr size_t DATA_SIZE = 1024;

int main(int argc, char* argv[]) {
    if(argc != 4) {
        std::cerr << "Invalid command arguments. Usage: " << argv[0] << " [ip] [port] [max connect]" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string ip_address = argv[1];
    uint16_t port = atoi(argv[2]);
    int max_connection = atoi(argv[3]);

    auto handler = [](epoll_server::Connection& conn) {
        if (conn.input_data_length() == 0) {
            std::cout << "Client connected. Ip =  " << conn.get_dst_addr()
                << " port = " << conn.get_dst_port() << std::endl;
        }

        uint32_t event = conn.get_event();
        if (event & EPOLLHUP || event & EPOLLERR) {
            std::cout << "Client disconnected. Ip = " << conn.get_dst_addr()
                << " port = " << conn.get_dst_port();
        }

        if (event & EPOLLIN) {
            std::string buff(DATA_SIZE, '\0');
            try {
                size_t bytes_read = conn.read(buff.data(), DATA_SIZE);
                std::cout << "Bytes read: " << bytes_read << ". Ip = "
                    << conn.get_dst_addr() << " port = " << conn.get_dst_port() << std::endl;

            } catch (const epoll_server::ConnectionError& err) {
                std::cout << err.what() << " Ip = " << conn.get_dst_addr()
                    << " port = " << conn.get_dst_port() << std::endl;
                throw err;
            } catch (const epoll_server::ReadError& err) {
                std::cerr << err.what();
                throw err;
            }
        }

        if (event & EPOLLOUT) {
            try {
                size_t bytes_written = conn.write(conn.get_input_data().c_str(), conn.input_data_length());
                std::cout << "Bytes written: " << bytes_written << ". Ip = "
                         << conn.get_dst_addr() << " port = " << conn.get_dst_port() << std::endl;
            } catch (const epoll_server::WriteError& err) {
                std::cerr << err.what() << std::endl;
                throw err;
            }
        }
    };
    try {
        epoll_server::Server server(ip_address, port, max_connection, handler);
        server.start();
    } catch (const epoll_server::RuntimeError& err) {
        std::cerr << err.what() << std::endl;
    } catch (const epoll_server::InvalidArgument& err) {
        std::cerr << err.what() << std::endl;
    }
}
