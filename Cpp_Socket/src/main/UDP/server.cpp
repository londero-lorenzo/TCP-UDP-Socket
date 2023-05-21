//
// Created by Londero Lorenzo on ~ April 2023.
//



#include "../../UDP/Server.h"

int main() {

    int port = 5500;

    Socket::UDP::Server server;

    server.start(port);

    server.close();
    return 0;
}