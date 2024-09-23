#include "socket-acceptor.hpp"
#include "socket-addr.hpp"
#include <unistd.h>  // For close()
#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <algorithm>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;
constexpr int THREAD_POOL_SIZE = 10;

std::queue<int> clientQueue;
std::mutex queueMutex;
std::condition_variable condition;

void handleSession(int clientSocket) {
    std::vector<char> buffer(BUFFER_SIZE);
    ssize_t bytesRead = recv(clientSocket, buffer.data(), buffer.size(), 0);

    if (bytesRead > 0) {
        std::cout << "Received data: " << std::string(buffer.data(), bytesRead) << std::endl;
    }

    // Send response
    std::string response_str = "ACK of received data!";
    std::vector<char> response(response_str.begin(), response_str.end());
    send(clientSocket, response.data(), response.size(), 0);

    close(clientSocket);  // Close the connection after session
}

void worker() {
    while (true) {
        int clientSocket;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [] { return !clientQueue.empty(); });

            clientSocket = clientQueue.front();
            clientQueue.pop();
        }

        handleSession(clientSocket);
    }
}

int main() {
    SocketAddr addr("0.0.0.0", PORT);
    auto acceptor = std::make_unique<SocketAcceptor>(addr);

    acceptor->bind();
    acceptor->listen();

    std::cout << "Server is listening on port " << PORT << std::endl;

    // Start thread pool
    std::vector<std::thread> threadPool;
    for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
        threadPool.emplace_back(worker);
    }

    while (true) {
        int clientSocket = acceptor->acceptConnection();
        if (clientSocket < 0) continue;

        // Push client socket to the queue
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            clientQueue.push(clientSocket);
        }
        condition.notify_one();
    }

    // Join threads (if needed for cleanup, though this will run indefinitely)
    for (auto& thread : threadPool) {
        thread.join();
    }

    return 0;
}
