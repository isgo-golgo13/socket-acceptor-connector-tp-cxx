# Socket Acceptor-Connector Thread Pool
C++20 POSA 2 Socket Acceptor-Connector Design Pattern for Client and Server using Thread-Pool (TP) from ACE C++ Framework


## Thread Per-Connection vs Thread Pool Differences

The following are the differences of Thread Per-Connection vs Thread Pool.

- Thread Pool: The server will now create a fixed number of threads at startup. These threads will pull tasks (client sessions) from a queue.

- Task Queue: The server will use a std::deque for storing tasks (client connections), and a worker thread from the pool will pick up tasks from this queue.

## Compiling the Project

```shell
cmake -S . -B ./dist 
```

Next produce the exes.

```shell
cmake --build ./dist
```

This root-level CMakeLists.txt will call on the `client/CMakeLists.txt` and `server/CMakeLists.txt` files that in-turn will require to create the `svckit` Unix shared library.


## Project Structure

The project structure is as follows.

```shell
├── CMakeLists.txt
├── Dockerfile.client
├── Dockerfile.server
├── README.md
├── client
│   ├── CMakeLists.txt
│   └── client.cpp
├── docker-compose.yaml
├── server
│   ├── CMakeLists.txt
│   └── server.cpp
└── svckit
    ├── CMakeLists.txt
    ├── socket.cpp
    ├── socket.hpp
    ├── socket-acceptor.cpp
    ├── socket-acceptor.hpp
    ├── socket-addr.cpp
    ├── socket-addr.hpp
    ├── socket-connector.cpp
    ├── socket-connector.hpp
    ├── thread-pool.cpp
    ├── thread-pool.hpp
    ├── thread.cpp
    └── thread.hpp
```


## Fix Changelist

- Fix class `SockAddr` in socket-addr.hpp and .cpp to include `struct sockaddr_in` as a private instance to the class and SockAddr is an API facade for struct sockaddr_in.



