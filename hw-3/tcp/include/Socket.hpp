#ifndef SOCKET_HPP
#define SOCKET_HPP

namespace tcp {

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
    bool is_opened() const;
    void open();
    void close();

private:
    int fd_;

};

} // namespace tcp

#endif // SOCKET_HPP
