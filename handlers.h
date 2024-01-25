#pragma once

#include "nats_server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <optional>


class AbsractHandler {
public:
    virtual ~AbsractHandler() {}
    AbsractHandler(COMMAND_TYPE type) : type_(type) {}
    virtual void Handle(int client_socket_fd, std::vector<Subscription>& subscribers) = 0;
    std::string GetMessage() { return ack_message_; }
    COMMAND_TYPE GetType() { return type_; }
protected:
    std::string ack_message_ = "-ERR\n";
    COMMAND_TYPE type_;
};

class SubCommandHandler : public AbsractHandler {
public:
    SubCommandHandler(std::string topic, COMMAND_TYPE type) : AbsractHandler(type), topic_(topic) {}

    void Handle(int client_socket_fd, std::vector<Subscription>& subscribers) override;
private:
    std::string topic_;
};

class PubCommandHandler : public AbsractHandler {
public:
    PubCommandHandler(std::string topic, COMMAND_TYPE type) : AbsractHandler(type), topic_(topic) {}

    void Handle(int client_socket_fd, std::vector<Subscription>& subscribers) override;
private:
    std::string topic_;
};

class UnsubCommandHandler : public AbsractHandler {
public:
    UnsubCommandHandler(std::string topic, COMMAND_TYPE type) : AbsractHandler(type), topic_(topic) {}

    void Handle(int client_socket_fd, std::vector<Subscription>& subscribers) override;
private:
    std::string topic_;
};

class PingCommandHandler : public AbsractHandler {
public:
    PingCommandHandler(COMMAND_TYPE type) : AbsractHandler(type) {}

    void Handle(int client_socket_fd, std::vector<Subscription>& subscribers) override;
};