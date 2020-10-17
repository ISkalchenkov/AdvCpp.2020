#ifndef FILE_DESCRIPTOR_HPP
#define FILE_DESCRIPTOR_HPP

namespace epoll_server {

class FileDescriptor {
public:
    FileDescriptor();
    explicit FileDescriptor(int fd);

    FileDescriptor(const FileDescriptor& rhs) = delete;
    FileDescriptor(FileDescriptor&& rhs) noexcept;

    FileDescriptor& operator=(const FileDescriptor& rhs) = delete;
    FileDescriptor& operator=(FileDescriptor&& rhs);

    FileDescriptor& operator=(int fd);

    ~FileDescriptor() noexcept;

    [[nodiscard]] bool is_opened() const;
    [[nodiscard]] int get_fd() const;
    void set_fd(int fd);
    int extract();

    void close();

private:
    int fd_;

};

} // namespace epoll_server

#endif // FILE_DESCRIPTOR_HPP
