#include <sys/socket.h>
#include <netinet/in.h>
#include "nats_server.h"
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "parser.h"
#include "handlers.h"

NATSServer::NATSServer() {
    sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd_ == -1) {
        std::cerr << "Error creating socket\n";
        return;
    }

    memset(&serverAddr_, 0, sizeof(serverAddr_));
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_addr.s_addr = INADDR_ANY;
    serverAddr_.sin_port = htons(4222);

    if (bind(sock_fd_, (struct sockaddr*)&serverAddr_, sizeof(serverAddr_)) == -1) {
        std::cerr << "Error binding socket\n";
        return;
    }

    listen(sock_fd_, 10);
}

void NATSServer::Start() {
    while (true) {
        int client_socket_fd = accept(sock_fd_, NULL, NULL);
        if (client_socket_fd == -1) {
            std::cerr << "Error accepting connection\n";
            return;
        }
        HandleClient(client_socket_fd);
    }
}

void NATSServer::HandleClient(int client_socket_fd) {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    char clientIP[INET_ADDRSTRLEN];
    if (getpeername(client_socket_fd, (struct sockaddr*)&clientAddr, &clientAddrLen) == 0) {
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
        std::cout << "Client connected from IP: " << clientIP << std::endl;

    } else {
        std::cerr << "Error getting client IP\n";
    }
    std::string infoMessage = "INFO {\"host\":\"0.0.0.0\",\"port\":4222,\"client_ip\":\"" + std::string(clientIP) + "\"}\r\n";
    send(client_socket_fd, infoMessage.c_str(), infoMessage.size(), 0);

    // Keep reading from client until they disconnect
    while (true) {
        Command* command = new Command();
        char * buffer = new char[1024];
        int bytesReceived = recv(client_socket_fd, buffer, 1024, 0);

        if (bytesReceived <= 0) {
            // Client has closed the connection
            std::cout << "Client disconnected\n";
            // TODO: Remove the client from the subscribers list
            break;
        }
        command->input = std::string(buffer);
        auto command_handler = CommandParser::parse(command);
        if (command_handler) {
            command_handler->Handle(client_socket_fd, subscribers_);
            send(client_socket_fd, command_handler->GetMessage().c_str(), command_handler->GetMessage().size(), 0);
        }
    }

    close(client_socket_fd);
}