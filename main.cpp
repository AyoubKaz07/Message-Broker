#include <iostream>
#include "nats_server.h"

int main() {
    std::cout << "Hello from main!" << std::endl;

    // Example usage of your NATSServer and parser
    NATSServer server;
    server.Start();

    return 0;
}
