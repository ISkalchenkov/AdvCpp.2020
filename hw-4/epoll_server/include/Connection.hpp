#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "FileDescriptor.hpp"

#include <string>
#include <netinet/in.h>

namespace epoll_server {

class Connection {
public:
    Connection(const std::string& address, uint16_t port);
    Connection(int fd, int epoll_fd, const sockaddr_in& client_addr);

    Connection(const Connection& rhs) = delete;
    Connection& operator=(const Connection& rhs) = delete;

    Connection(Connection&& rhs) noexcept;
    Connection& operator=(Connection&& rhs) noexcept;

    void connect(const std::string& address, uint16_t port);
    void close();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void set_event(uint32_t event);
    [[nodiscard]] uint32_t get_event() const;

    [[nodiscard]] uint16_t get_dst_port() const;
    [[nodiscard]] const std::string& get_dst_addr() const;

    [[nodiscard]] size_t input_data_length() const;
    [[nodiscard]] const std::string& get_input_data() const;
    [[nodiscard]] bool is_opened() const;

    void modify_epoll(uint32_t event);

private:
    int create_socket();

private:
    FileDescriptor socket_;
    int epoll_fd_;

    std::string input_data_;
    uint32_t event_;
    uint16_t dst_port_;
    std::string dst_addr_;
};

} // namespace epoll_server

#endif // CONNECTION_HPP
