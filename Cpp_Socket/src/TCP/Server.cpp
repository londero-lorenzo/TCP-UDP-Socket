//
// Created by Londero Lorenzo on ~ April 2023.
//


#include "Server.h"
#include "Client.h"
#include "../utils/IpResolver.cpp"
#include <Winsock2.h>

namespace Socket::TCP {

    Server::Server() {
        // viene caricata la struttura contenente le informazioni per l'implementazione dei Socket in Windows
        int result = WSAStartup(MAKEWORD(2, 2), &(Server::wsaData));
        // viene controllato il risultato del caricamento
        if (result != 0) {
            std::cerr << "Errore durante il caricamento di WSAStartup: " << result << std::endl;
            return;
        }

        // AF_INET = famiglia dell'indirizzo utilizzato per il socket (IPv4)
        // SOCK_STREAM = la comunicazione utilizza dei flussi dati bidirezionali
        // IPPROTO_TCP = indica il protocollo della comunicazione (TCP)
        Server::listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        // viene verificato che l'oggetto socket creato sia valido
        if (Server::listenSock == INVALID_SOCKET) {
            std::cerr << "Socket invalido: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }
    }


    void Server::start(int port) {
        // vengono impostati i parametri per permettere la connessione
        Server::serverAddr.sin_addr.s_addr = INADDR_ANY; // qualsiasi indirizzo i<p
        Server::serverAddr.sin_port = htons(port);
        Server::serverAddr.sin_family = AF_INET;
        // viene richiamato il metodo interno per permettere al socket di essere raggiunto alla data porta
        int result = bind(listenSock, (struct sockaddr *) (&serverAddr), sizeof(serverAddr));
        // viene verificato che non siano insorti errori
        if (result == SOCKET_ERROR) {
            std::cerr << "Errore durante l'apertura della porta: " << port << std::endl << WSAGetLastError()
                      << std::endl;
            closesocket(Server::listenSock);
            WSACleanup();
            return;
        }

        // Inizia ad ascoltare le connessioni in entrata
        Server::listen();

        Socket::TCP::Client client(&(Server::listenSock));
        char *data = client.receive();

        client.send(data);
        client.close();
    }

    int Server::listen() const {
        //std::cout << "Server avviato all'indirizzo: " << getMyIp() << ":" << Server::getPort() << std::endl;
        std::cout << "In attesa di una connessione ..." << std::endl;

        int result = ::listen(Server::listenSock, SOMAXCONN);
        if (result == SOCKET_ERROR) {
            std::cerr << "Errore durante l'ascolto alla porta: " << Server::getPort() << std::endl << WSAGetLastError()
                      << std::endl;
            closesocket(Server::listenSock);
            WSACleanup();
        }
        return result;
    }

    int Server::getPort() const {
        return Server::serverAddr.sin_port;
    }

    // definizione
    void Server::close() const {
        closesocket(Server::listenSock);
    }
}