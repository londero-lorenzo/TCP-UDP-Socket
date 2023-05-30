//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene verificato che il file header per il client non sia già stato definito
#ifndef SOCKET_TCP_CLIENT_H

// viene definito l'identificatore per questo file header associato all'oggetto a cui fa riferimento
#define SOCKET_TCP_CLIENT_H

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
     * Classe Client utilizzata per le comunicazioni TCP.
     */
    class Client {
    // vengono dichiarate le variabili private associate a questo oggetto
    private:
        // struttura contenente le informazioni per l'implementazione dei Socket in Windows
        WSAData wsaData{};

        // variabile tipo SOCKET utilizzata per avere un riferimento alla struttura Socket
        SOCKET sock;

        // struttura destinata per ospitare le informazioni relative all'indirizzo del destinatario
        sockaddr_in destinationAddr{};

        // struttura destinata per ospitare le informazioni relative all'indirizzo del client stesso
        sockaddr_in clientAddr{};

        // valore intero relativo alla grandezza della struttura dati contenente l'indirizzo del client stesso
        int clientAddrLen = sizeof(clientAddr);

        // buffer di caratteri utilizzato per essere riempito con i dati in ricezione
        char receivingBuffer[1024]{};

    // vengono dichiarate le variabili pubbliche associate a questo oggetto
    public:
        // viene dichiarato il costruttore pubblico
        Client();

        // viene dichiarato un costruttore pubblico alternativo
        explicit Client(const SOCKET *serverSock);

        // viene dichiarato il metodo void per permettere la connessione al server
        void connectTo(char *ip, int port);

        // viene dichiarato il metodo void per permettere d'inviare dati al server
        void send(char *data) const;

        // viene dichiarato il metodo void per permettere la ricezione dei dati dal server
        char *receive();

        // viene dichiarato il metodo per ottenere l'indirizzo ip di questo socket
        [[nodiscard]] char *getIp();

        // viene dichiarato il metodo per chiudere il socket
        void close() const;
    };

} // viene chiuso lo spazio logico nel quale è presente questo oggetto

#endif //SOCKET_TCP_CLIENT_H
