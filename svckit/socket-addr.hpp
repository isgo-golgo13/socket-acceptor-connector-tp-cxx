#pragma once

#include <string>
#include <arpa/inet.h>

class SocketAddr {
public:
    SocketAddr() = default;
    // SocketAddr(const sockaddr_in& addr);
    SocketAddr(const std::string& ip, int port);
    SocketAddr(const SocketAddr& other) = default;
    SocketAddr(SocketAddr&& other) noexcept = default;
    SocketAddr& operator=(const SocketAddr& other) = default;
    SocketAddr& operator=(SocketAddr&& other) noexcept = default;
    ~SocketAddr() = default;

    [[nodiscard]] std::string getIp() const;
    [[nodiscard]] int getPort() const;
    //[[nodiscard]] sockaddr_in getAddr() const;
private:
    //struct sockaddr_in addr_;
    std::string ip_;
    int port_;
};
