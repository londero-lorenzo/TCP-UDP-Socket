//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene verificato che il file header per il server non sia già stato definito
#ifndef CPP_SOCKET_SERVER_H

// viene definito l'identificatore per questo file header associato all'oggetto a cui fa riferimento
#define CPP_SOCKET_SERVER_H

// vengono incluse le librerie utili per il funzionamento del socket
#include <Winsock2.h>
#include <iostream>

// viene aggiunta la libreria "ws2_32.lib" alla lista delle librerie utili per il funzionamento del socket
#pragma comment(lib, "ws2_32.lib")

// viene definito lo spazio logico nel quale si troverà l'oggetto di seguito definito
/**
 * Spazio logico nel quale sono racchiusi tutti gli oggetti Socket
 */
namespace Socket::TCP {
    class Server {
    private:
        // struttura contenente le informazioni per l'implementazione dei Socket in Windows
        WSAData wsaData{};

        SOCKET listenSock;

        // struttura contenente varie informazioni per il funzionamento del socket
        sockaddr_in serverAddr{};

        [[nodiscard]] int listen() const;



    public:
        // viene dichiarato un costruttore pubblico
        Server();

        // viene dichiarato un metodo void per permettere al socket di essere raggiungibile a una data porta
        void start(int port);

        [[nodiscard]] int getPort() const;

        void close() const;

    };
} // Socket

#endif //CPP_SOCKET_SERVER_H
