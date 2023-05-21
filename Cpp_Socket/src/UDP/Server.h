//
// Created by Londero Lorenzo on ~ April 2023.
//

#ifndef CPP_SOCKET_SERVER_H
#define CPP_SOCKET_SERVER_H

#include <Winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")


namespace Socket::UDP {
    class Server {
    private:
        // struttura contenente le informazioni per l'implementazione dei Socket in Windows
        WSAData wsaData{};

        SOCKET listenSock;

        // struttura contenente varie informazioni per il funzionamento del socket
        sockaddr_in serverAddr{};


    public:
        // viene dichiarato un costruttore pubblico
        Server();

        // viene dichiarato un metodo void per permettere al socket di essere raggiungibile a una data porta
        void start(int port);

        void close() const;

    };
} // Socket

#endif //CPP_SOCKET_SERVER_H
