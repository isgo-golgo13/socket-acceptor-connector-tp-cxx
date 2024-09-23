#include "socket-connector.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <memory>

constexpr int SESSION_COUNT = 6;  // Number of client sessions
constexpr auto PAYLOAD = "Hello, Server!";  // Data to send
constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 8080;

void sendSession() {
    // Create and connect SocketConnector
    SocketAddr addr("127.0.0.1", PORT);
    SocketConnector connector(addr);
    connector.connect();

    // Send data
    connector.sendData(PAYLOAD, strlen(PAYLOAD));

    // Receive response
    char buffer[BUFFER_SIZE];
    connector.recvData(buffer, sizeof(buffer));
    std::cout << "Received from server: " << buffer << std::endl;
}

int main() {
    std::vector<std::thread> sessions;
    sessions.reserve(SESSION_COUNT);

    for (int i = 0; i < SESSION_COUNT; ++i) {
        sessions.emplace_back(sendSession);
    }

    for (auto& session : sessions) {
        session.join();
    }

    return 0;
}
