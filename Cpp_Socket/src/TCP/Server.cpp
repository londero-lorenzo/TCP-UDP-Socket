//
// Created by Londero Lorenzo on ~ April 2023.
//


#include "Server.h"
#include "Client.h"
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

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
        Server::serverAddr.sin_addr.s_addr = INADDR_ANY; // qualsiasi indirizzo ip
        Server::serverAddr.sin_port = htons(port);
        Server::serverAddr.sin_family = AF_INET;
        // viene richiamato il metodo interno per permettere al socket di essere raggiunto alla data porta
        int result = bind(listenSock, (struct sockaddr *)(&serverAddr), sizeof(serverAddr));
        // viene verificato che non siano insorti errori
        if (result == SOCKET_ERROR) {
            std::cerr << "Errore durante l'apertura della porta: " << port << std::endl << WSAGetLastError()
                      << std::endl;
            closesocket(Server::listenSock);
            WSACleanup();
            return;
        }

        // Inizia ad ascoltare le connessioni in entrata
        result = listen(listenSock, SOMAXCONN);
        if (result == SOCKET_ERROR) {
            std::cerr << "Errore durante l'ascolto alla porta: " << port << std::endl << WSAGetLastError() << std::endl;
            closesocket(listenSock);
            WSACleanup();
            return;
        }

        std::cout << "In attesa di una connessione" << " alla porta: " << port << " ..." << std::endl;
        sockaddr_in clientAddr{};
        int clientAddrLen = sizeof(clientAddr);
        SOCKET clientSock = accept(listenSock, (struct sockaddr *) &clientAddr, &clientAddrLen);

        Socket::TCP::Client client(&clientSock, clientAddr);
        char *clientIp = client.getIp();
        char *data = client.receive();
        std::cout << "Connessione da: " << clientIp << std::endl;
        std::cout << "Data:" << std::endl << data << std::endl;
        client.send(data);
        client.close();
    }

    // definizione
    void Server::close() const
    {
        closesocket(Server::listenSock);
    }
}
