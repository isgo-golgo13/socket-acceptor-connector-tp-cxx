#include "socket-acceptor.hpp"
#include "socket-addr.hpp"
#include "thread-pool.hpp"
#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;
constexpr size_t THREAD_POOL_SIZE = 4;  // Adjust pool size as needed

void handleSession(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead > 0) {
        std::cout << "Received data: " << std::string(buffer, bytesRead) << std::endl;
    }

    close(clientSocket);  // Close the connection after session
}

int main() {
    SocketAddr addr("0.0.0.0", PORT);  // Listen on all interfaces
    auto acceptor = std::make_unique<SocketAcceptor>(addr);
    ThreadPool threadPool(THREAD_POOL_SIZE);  // Create a thread pool

    acceptor->bind();
    acceptor->listen();

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        int clientSocket = acceptor->acceptConnection();

        // Enqueue a task for the thread pool
        threadPool.enqueueTask([clientSocket]() {
            handleSession(clientSocket);
        });
    }

    return 0;
}
