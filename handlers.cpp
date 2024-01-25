#include "handlers.h"
#include <algorithm>

void SubCommandHandler::Handle(int client_socket_fd, std::vector<Subscription>& subscribers) {
    // Check if the client is already subscribed to the topic
    auto it = std::find_if(subscribers.begin(), subscribers.end(),
                            [client_socket_fd, this](const Subscription& subscription) {
                                return subscription.client_socket_fd == client_socket_fd && subscription.topic == topic_;
                            });

    if (it != subscribers.end()) {
        std::cout << "Already subscribed to the topic: " << topic_ << std::endl;
        ack_message_ = "-ERR Already subscribed to the topic\r\n";
        return;
    }

    // Add the new subscription to the list
    Subscription newSubscription{client_socket_fd, topic_};
    subscribers.push_back(newSubscription);
    
    ack_message_ = "+OK\n";
}

void PubCommandHandler::Handle(int client_socket_fd, std::vector<Subscription>& subscribers) {
    auto it = std::find_if(subscribers.begin(), subscribers.end(),
                            [client_socket_fd, this](const Subscription& subscription) {
                                return subscription.client_socket_fd == client_socket_fd && subscription.topic == topic_;
                            });

    // Read Message
    char buffer[1024];
    int bytes_read = recv(client_socket_fd, buffer, 1024, 0);
    std::string message(buffer);

    if (bytes_read <= 0) {
        // Client has closed the connection
        std::cout << "Client disconnected\n";
        // TODO: Remove the client from the subscribers list
        return;
    }

    // Find subscribers to the topic and send the message to them
    for (const auto& subscriber : subscribers) {
        if (subscriber.topic == topic_) {
            send(subscriber.client_socket_fd, message.c_str(), message.size(), 0);
        }
    }
    ack_message_ = "+OK\n";
}

void UnsubCommandHandler::Handle(int client_socket_fd, std::vector<Subscription>& subscribers) {
    auto predicate = [client_socket_fd, this](const Subscription& subscription) {
        return subscription.client_socket_fd == client_socket_fd && subscription.topic == topic_;
    };
    subscribers.erase(std::remove_if(subscribers.begin(), subscribers.end(), predicate), subscribers.end());
    
    ack_message_ = "+OK\n";
}

void PingCommandHandler::Handle(int client_socket_fd, std::vector<Subscription>& subscribers) {
    ack_message_ = "PONG\n";
}