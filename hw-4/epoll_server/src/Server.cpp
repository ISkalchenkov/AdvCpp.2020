#include "Server.hpp"
#include "Exception.hpp"

#include <arpa/inet.h>

namespace epoll_server {

Server::Server(const std::string &address, uint16_t port, int max_connect, const Callback& handler)
    : handler_(handler) {

    open(address, port);
    set_max_connect(max_connect);
    create_epoll();
    epoll_ctl(server_fd_.get_fd(), EPOLLIN, CtlOption::ADD);
}

void Server::open(const std::string &address, uint16_t port) {
    server_fd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (server_fd_.get_fd() < 0) {
        throw SocketError("Error creating socket: ");
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_aton(address.c_str(), &addr.sin_addr) < 0) {
        throw AddressError("Error parsing IP address, ip = " + address);
    }

    if (bind(server_fd_.get_fd(),
            reinterpret_cast<sockaddr*>(&addr),
            sizeof(addr)) < 0) {
        throw SocketError("Socket binding error: ");
    }
}

void Server::set_max_connect(int max_connect) {
    if (listen(server_fd_.get_fd(), max_connect) < 0) {
        throw SocketError("Socket listen error: ");
    }
}

bool Server::is_opened() const {
    return server_fd_.is_opened();
}

void Server::close() {
    server_fd_.close();
    epoll_fd_.close();
}

void Server::create_epoll() {
    epoll_fd_ = epoll_create(1);
    if (epoll_fd_.get_fd() < 0) {
        throw EpollError("Error creating epoll: ");
    }
}

void Server::epoll_ctl(int fd, uint32_t events, CtlOption op) {
    epoll_event event{};
    event.data.fd = fd;
    event.events = events;

    if (::epoll_ctl(epoll_fd_.get_fd(), static_cast<int>(op), fd, &event) < 0) {
        throw EpollError("Epoll_ctl error: ");
    }
}

void Server::start() {
    constexpr size_t EPOLL_SIZE = 128;
    epoll_event events[EPOLL_SIZE];

    while(true) {
        int nfds = epoll_wait(epoll_fd_.get_fd(), events, EPOLL_SIZE, -1);
        if (nfds < 0) {
            if (errno == EINTR)
                continue;
            throw EpollError("Epoll waiting error: ");
        }

        for (int n = 0; n < nfds; n++) {
            int fd = events[n].data.fd;
            uint32_t event = events[n].events;

            if (fd == server_fd_.get_fd())
                accept_clients();
            else
                handle_client(fd, event);
        }
    }
}

void Server::accept_clients() {
    sockaddr_in client_addr{};
    socklen_t addr_size = sizeof(client_addr);

    while (true) {
        int fd = accept4(server_fd_.get_fd(),
                reinterpret_cast<sockaddr*>(&client_addr),
                &addr_size, SOCK_NONBLOCK);
        if (fd < 0) {
            if (errno == EINTR)
                continue;
            else if (errno == EWOULDBLOCK || errno == EAGAIN)
                return;
            else
                throw SocketError("Socket accept error: ");
        }

        clients_.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(fd),
                std::forward_as_tuple(fd, client_addr));

        epoll_ctl(fd, EPOLLIN, CtlOption::ADD);
    }
}

void Server::handle_client(int fd, uint32_t event) {
    Connection& connection = clients_.at(fd);
    connection.set_event(event);

    try {
        handler_(connection);
    } catch (...) {
        clients_.erase(fd);
    }

    if (event & EPOLLHUP || event & EPOLLERR) {
        clients_.erase(fd);
        return;
    }
}

} // namespace epoll_server