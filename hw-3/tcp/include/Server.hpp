#ifndef SERVER_HPP
#define SERVER_HPP

#include "Connection.hpp"

namespace tcp {

class Server {
public:
    Server(const std::string& address, uint16_t port, int max_connect = 0);

    Server(const Server& rhs) = delete;
    Server(Server&& rhs) noexcept;

    Server& operator=(const Server& rhs) = delete;
    Server& operator=(Server&& rhs) noexcept;

    ~Server() noexcept;

    void open(const std::string& address, uint16_t port, int max_connect = 0);
    void close();

    Connection accept();
    void set_max_connect(int max_connect);

    bool is_opened() const;

private:
    Socket socket_;
    bool is_opened_;
};

} // namespace tcp

#endif // SERVER_HPP
