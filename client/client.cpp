#include "socket-connector.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

constexpr int SESSION_COUNT = 100;  // Number of sessions to send
constexpr auto PAYLOAD = "000000000-1010-Payload";  // Data buffer to send
constexpr int PORT = 8080;

void sendSession() {
    SocketAddr addr("127.0.0.1", PORT);
    auto connector = std::make_unique<SocketConnector>(addr);

    connector->connect();
    connector->sendData(PAYLOAD);
}

int main() {
    std::vector<std::thread> sessions;
    sessions.reserve(SESSION_COUNT);

    // Launch 100 sessions (thread-per-session)
    for (int i = 0; i < SESSION_COUNT; ++i) {
        sessions.emplace_back(sendSession);
    }

    // Join all session threads
    for (auto& session : sessions) {
        session.join();
    }

    return 0;
}
