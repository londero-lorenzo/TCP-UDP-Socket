//
// Created by Londero Lorenzo on ~ April 2023.
//


#ifndef CPP_SOCKET_CLIENT_H
#define CPP_SOCKET_CLIENT_H


#define CLIENT 0
#define SERVER 1

#include <Winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

namespace Socket::UDP {

    class Client {
    private:
        // struttura contenente le informazioni per l'implementazione dei Socket in Windows
        WSAData wsaData{};

        SOCKET sock;

        // struttura contenente varie informazioni per il funzionamento del socket
        sockaddr_in destinationAddr{};

        int destinationAddrLen = sizeof(destinationAddr);

        sockaddr_in clientAddr{};

        // buffer di caratteri utilizzato per essere riempito con i dati in ricezione
        char receivingBuffer[1024]{};

        int side;


    public:
        // viene dichiarato un costruttore pubblico
        Client();

        explicit Client(const SOCKET *clientSock);

        // viene dichiarato un metodo void per permettere la connessione al server
        void connectTo(char *ip, int port);

        // viene dichiarato un metodo void per permettere d'inviare dati al server
        void send(char *data);

        // viene dichiarato un metodo void per permettere la ricezione dei dati dal server
        char *receive();

        char *getIp();

        int getPort() const;

        void close() const;
    };

} // Socket

#endif //CPP_SOCKET_CLIENT_H
