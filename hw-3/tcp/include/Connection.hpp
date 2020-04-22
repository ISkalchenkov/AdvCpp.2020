#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <netinet/in.h>

#include "Socket.hpp"

namespace tcp {

class Connection {
public:
    Connection(const std::string& address, uint16_t port);

    Connection(const Connection& rhs) = delete;
    Connection& operator=(const Connection& rhs) = delete;

    Connection(Connection&& rhs) noexcept;
    Connection& operator=(Connection&& rhs) noexcept;

    ~Connection() noexcept;

    void connect(const std::string& address, uint16_t port);
    void close();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void set_send_timeout(int sec);
    void set_receive_timeout(int sec);

    uint16_t get_dst_port() const;
    const std::string& get_dst_addr() const;

    bool is_opened() const;

private:
    Connection(int fd, sockaddr_in client_addr);
    friend class Server;

private:
    Socket socket_;
    bool is_opened_;

    uint16_t dst_port_;
    std::string dst_addr_;
};

} // namespace tcp

#endif // CONNECTION_HPP
