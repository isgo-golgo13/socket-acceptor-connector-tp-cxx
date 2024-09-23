#include "socket-connector.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

constexpr int SESSION_COUNT = 100;
constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 8080;

void sendTask(int clientID) {
    // Use std::string for payload
    std::string payload_str = "Payload-" + std::to_string(clientID);
    std::vector<char> payload(payload_str.begin(), payload_str.end());

    // Create and connect SocketConnector
    SocketAddr addr("127.0.0.1", PORT);
    SocketConnector connector(addr);
    connector.connect();

    // Send data
    connector.sendData(payload);

    // Receive response
    std::vector<char> buffer(BUFFER_SIZE);
    connector.recvData(buffer);
    std::cout << "Client " << clientID << " received from server: " << std::string(buffer.data(), buffer.size()) << std::endl;
}

int main() {
    std::vector<std::thread> threadPool;
    threadPool.reserve(SESSION_COUNT);

    // Launch threads in the pool
    for (int i = 0; i < SESSION_COUNT; ++i) {
        threadPool.emplace_back(sendTask, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate staggered connections
    }

    // Wait for all threads to complete
    for (auto& thread : threadPool) {
        thread.join();
    }

    return 0;
}
