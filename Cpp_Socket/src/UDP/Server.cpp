//
// Created by Londero Lorenzo on ~ April 2023.
//



#include "Server.h"
#include "Client.h"
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

namespace Socket::UDP {

    Server::Server() {
        // viene caricata la struttura contenente le informazioni per l'implementazione dei Socket in Windows
        int result = WSAStartup(MAKEWORD(2, 2), &(Server::wsaData));
        // viene controllato il risultato del caricamento
        if (result != 0) {
            std::cerr << "Errore durante il caricamento di WSAStartup: " << result << std::endl;
            return;
        }

        // AF_INET = famiglia dell'indirizzo utilizzato per il socket (IPv4)
        // SOCK_DGRAM = la comunicazione permette solamente un invio e una ricezione
        // IPPROTO_UDP = indica il protocollo della comunicazione (UDP)
        Server::listenSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
        int result = bind(Server::listenSock, (struct sockaddr *) &(Server::serverAddr), sizeof(serverAddr));
        // viene verificato che non siano insorti errori
        if (result == SOCKET_ERROR) {
            std::cerr << "Errore durante l'apertura della porta: " << port << std::endl << WSAGetLastError()
                      << std::endl;
            closesocket(Server::listenSock);
            WSACleanup();
            return;
        }

        std::cout << "In attesa di dati..." << std::endl;

        Socket::UDP::Client client(&(Server::listenSock));

        char *data = client.Receive();

        client.Send(data);

        client.close();
    }

    // definizione
    void Server::close() const {
        closesocket(Server::listenSock);
    }
}
