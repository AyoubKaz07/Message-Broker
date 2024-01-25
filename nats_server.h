#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <optional>

enum COMMAND_TYPE {
    PING,
    SUB,
    PUB,
    UNSUB,
    INVALID
};

struct Subscription {
    int client_socket_fd;
    std::string topic;
};

struct Command {
    COMMAND_TYPE type;
    std::string input;
};

class NATSServer {
public:
    NATSServer();

    void Start();
    void HandleClient(int client_socket_fd);

private:
    int sock_fd_;
    struct sockaddr_in serverAddr_;
    std::vector<Subscription> subscribers_;
};
