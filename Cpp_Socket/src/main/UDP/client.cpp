//
// Created by Londero Lorenzo on ~ April 2023.
//



#include "../../UDP/Client.h"

int main() {

    char *ip = new char[]{
            "192.168.178.134"
    };
    int port = 5500;

    char *stringToSend = new char[]{
            "Ciao mondo!"
    };

    Socket::UDP::Client client;

    client.connectTo(ip, port);

    client.Send(stringToSend);

    client.Receive();

    client.close();
    return 0;
}
