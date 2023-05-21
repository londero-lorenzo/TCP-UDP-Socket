//
// Created by Londero Lorenzo on ~ April 2023.
//


#ifndef CPP_SOCKET_CLIENT_H
#define CPP_SOCKET_CLIENT_H

#include <Winsock2.h>
#include <iostream>

namespace Socket::TCP {

    class Client {
    private:
        // struttura contenente le informazioni per l'implementazione dei Socket in Windows
        WSAData wsaData{};

        SOCKET sock;

        // struttura contenente varie informazioni per il funzionamento del socket
        sockaddr_in destinationAddr{};

        sockaddr_in clientAddr{};

        int clientAddrLen = sizeof(clientAddr);

        // buffer di caratteri utilizzato per essere riempito con i dati in ricezione
        char receivingBuffer[1024]{};


    public:
        // viene dichiarato un costruttore pubblico
        Client();

        explicit Client(SOCKET *serverSock);

        // viene dichiarato un metodo void per permettere la connessione al server
        void connectTo(char *ip, int port);

        // viene dichiarato un metodo void per permettere d'inviare dati al server
        void send(char *data) const;

        // viene dichiarato un metodo void per permettere la ricezione dei dati dal server
        char* receive();

        char* getIp();

        void close() const;
    };

} // Socket

#endif //CPP_SOCKET_CLIENT_H
