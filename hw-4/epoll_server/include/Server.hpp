#ifndef SERVER_HPP
#define SERVER_HPP

#include "Connection.hpp"

#include <functional>
#include <unordered_map>
#include <sys/epoll.h>

namespace epoll_server {

using Callback = std::function<void(Connection& c)>;

enum class CtlOption {
    ADD = EPOLL_CTL_ADD,
    DEL = EPOLL_CTL_DEL,
    MOD = EPOLL_CTL_MOD
};

class Server {
public:
    Server(const std::string& address, uint16_t port,
            int max_connect, const Callback& handler);

    Server(Server&& rhs) = default;
    Server& operator=(Server&& rhs) = default;

    Server(const Server& rhs) = delete;
    Server& operator=(const Server& rhs) = delete;

    void open(const std::string& address, uint16_t port);
    void set_max_connect(int max_connect);
    [[nodiscard]] bool is_opened() const;
    void close();

    void start();

private:
    void create_epoll();
    void epoll_ctl(int fd, uint32_t event, CtlOption op);
    void accept_clients();
    void handle_client(int fd, uint32_t event);

private:
    FileDescriptor server_fd_;
    FileDescriptor epoll_fd_;

    Callback handler_;
    std::unordered_map<int, Connection> clients_;

};

} // namespace epoll_server

#endif // SERVER_HPP
