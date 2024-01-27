#include <iostream>
#include "server.h"

int main() {
    Server server;
    std::cout << "Starting server...\n";
    server.Start();

    return 0;
}
