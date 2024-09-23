#include "socket-addr.hpp"


//SocketAddr::SocketAddr(const sockaddr_in& addr) : addr_(addr) {}

SocketAddr::SocketAddr(const std::string& ip, int port) : ip_(ip), port_(port) {

}

// TODO: Change to this from above 
// SocketAddr::SocketAddr(const std::string& ip, int port) : ip_(ip), port_(port) {
//     addr_.sin_family = AF_INET;
//     addr_.sin_addr.s_addr = inet_addr(ip.c_str());
//     addr_.sin_port = htons(port);
// }

// struct sockaddr_in& SocketAddr::getAddr() const {
    
//     return addr_;
// }

std::string SocketAddr::getIp() const {
    return ip_;
}

int SocketAddr::getPort() const {
    return port_;
}
