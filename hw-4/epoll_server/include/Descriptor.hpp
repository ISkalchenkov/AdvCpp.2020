#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

namespace epoll_server {

class Socket {
public:
    Socket();
    Socket(int fd);

    Socket(const Socket& rhs) = delete;
    Socket(Socket&& rhs) noexcept;

    Socket& operator=(const Socket& rhs) = delete;
    Socket& operator=(Socket&& rhs) noexcept;

    ~Socket() noexcept;

    int get_fd() const;
    int extract();
    void close();
    void open();
    bool is_opened() const;

private:
    int fd_;
};

} // namespace epoll_server


#endif // DESCRIPTOR_HPP
