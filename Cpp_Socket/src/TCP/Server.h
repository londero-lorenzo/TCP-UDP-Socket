//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene verificato che il file header per il server non sia già stato definito
#ifndef SOCKET_TCP_SERVER_H

// viene definito l'identificatore per questo file header associato all'oggetto a cui fa riferimento
#define SOCKET_TCP_SERVER_H

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
    /**
     * Classe Server utilizzata per le comunicazioni TCP.
     */
    class Server {
    // vengono dichiarate le variabili private associate a questo oggetto
    private:
        // struttura contenente le informazioni per l'implementazione dei Socket in Windows
        WSAData wsaData{};

        // variabile tipo SOCKET utilizzata per avere un riferimento alla struttura Socket
        SOCKET listenSock;

        // struttura contenente varie informazioni per il funzionamento del socket
        sockaddr_in serverAddr{};

        // dichiarazione del metodo atto ad accogliere i client che tentano di accedere al server
        [[nodiscard]] int listen() const;

    // vengono dichiarate le variabili pubbliche associate a questo oggetto
    public:
        // viene dichiarato il costruttore pubblico
        Server();

        // viene dichiarato un metodo void per permettere al socket di essere raggiungibile da una data porta
        void start(int port);

        // viene dichiarato il metodo utilizzato per ottenere la porta alla quale il server è raggiungibile
        [[nodiscard]] int getPort() const;

        // viene dichiarato il metodo per chiudere il socket
        void close() const;

    };
} // Socket

#endif //SOCKET_TCP_SERVER_H
