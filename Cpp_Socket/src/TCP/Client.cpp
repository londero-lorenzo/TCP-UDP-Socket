//
// Created by Londero Lorenzo on ~ April 2023.
//

// vengono incluse le librerie utili per il funzionamento del socket
#include "Client.h"
#include <Winsock2.h>
#include <ws2ipdef.h>
#include <WS2tcpip.h>
#include <string>
#include "../utils/Error.cpp"

#pragma comment(lib, "ws2_32.lib")

// viene definito lo spazio logico nel quale si troverà l'oggetto al suo interno
namespace Socket::TCP {

    /**
     * Costruttore pubblico generico, si occupa dell'inizializzazione dell'oggetto socket.
     */
    Client::Client() {
        // viene caricata la struttura contenente le informazioni per l'implementazione dei Socket in Windows
        int result = WSAStartup(MAKEWORD(2, 2), &(Client::wsaData));
        // viene controllato il risultato del caricamento
        if (result != 0) {
            printErrorBeforeWSAInit(new char[]{
                    "Errore durante il caricamento di WSAStartup."
            }, result);
            return;
        }
        // AF_INET = famiglia dell'indirizzo utilizzato per il socket (IPv4)
        // SOCK_STREAM = la comunicazione utilizza dei flussi dati bidirezionali
        // IPPROTO_TCP = indica il protocollo della comunicazione (TCP)
        Client::sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        // viene verificato che l'oggetto socket creato sia valido
        if (Client::sock == INVALID_SOCKET) {
            printWSAError(new char[]{
                    "Errore durante il caricamento del socket."
            });
            return;
        }
    }

    /**
     * Costruttore pubblico alternativo, utilizzato dalla parte server una volta che viene captato un tentativo di connessione.
     * @param serverSock
     */
    Client::Client(const SOCKET *serverSock) {
        int result = WSAStartup(MAKEWORD(2, 2), &(Client::wsaData));
        // viene controllato il risultato del caricamento
        if (result != 0) {
            printErrorBeforeWSAInit(new char[]{
                    "Errore durante il caricamento di WSAStartup."
            }, result);
            return;
        }

        SOCKET clientSock = accept(*serverSock, (struct sockaddr *) &(Client::clientAddr),
                                   &(Client::clientAddrLen));
        if (clientSock == INVALID_SOCKET) {
            printWSAError(new char[]{
                    "Errore durante il caricamento del socket."
            });
            return;
        }


        std::cout << "Connessione da: " << Client::getIp() << std::endl;
        Client::sock = clientSock;
    }


    /**
     * Metodo utilizzato per permettere la connessione al server.<br>
     * Perché un socket si possa connettere ad un server, è necessario fornire l'indirizzo ip e la porta sulla quale sta funzionando il servizio TCP.
     * @param ip Indirizzo ip del server al quale ci si vuole connettere
     * @param port Porta del server al quale ci si vuole connettere
     */
    void Client::connectTo(char *ip, int port) {

        std::cout << "Connessione a: " << ip << ":" << port << std::endl;

        // vengono impostati i parametri per permettere la connessione
        /*
         * Client::destinationAddr.sin_addr.s_addr = inet_addr(ip); -> inet_addr() è una funzione deprecata,
         * per questo motivo viene utilizzato la funzione InetPton
         */
        InetPton(AF_INET, ip, &Client::destinationAddr.sin_addr.s_addr);
        Client::destinationAddr.sin_port = htons(port);
        Client::destinationAddr.sin_family = AF_INET;
        // viene richiamato il metodo interno per permettere la connessione
        int result = connect(Client::sock, (struct sockaddr *) (&(Client::destinationAddr)),
                             sizeof(Client::destinationAddr));
        // viene verificato che non siano insorti errori nel momento della connessione
        if (result == SOCKET_ERROR) {
            std::string outputStringError =
                    "\nErrore durante l'inizializzazione della connessione verso: " + std::string(ip) + ":" +
                    std::to_string(port);

            printWSAError(outputStringError.data());
            closesocket(Client::sock);
            return;
        }

    }

    /**
     * Metodo utilizzato per permettere l'invio dei dati al server.
     * @param data Insieme dei caratteri da inviare al server
     */
    void Client::send(char *data) const {
        std::cout << std::endl << "> Trasmissione... <" << std::endl;
        std::cout << "Dati da inviare:" << std::endl << data << std::endl;
        // viene richiamato il metodo interno per permettere l'invio dei dati
        int result = ::send(Client::sock, data, (int) strlen(data), 0);
        // viene verificato che non siano insorti errori durante l'invio dei dati
        if (result == SOCKET_ERROR) {
            printWSAError(new char[]{
                    "Errore durante l'invio dei dati."
            });
            closesocket(Client::sock);
            return;
        } else
            std::cout << "Byte inviati: " << result << std::endl;
        std::cout << "> Fine Trasmissione <" << std::endl;
    }

    /**
     * Metodo utilizzato per ricevere la sequenza di caratteri in ricezione dal server.
     * @return La sequenza di caratteri contenuti nel buffer del client
     */
    char *Client::receive() {
        std::cout << std::endl << "> Ricezione... <" << std::endl;
        // viene richiamato il metodo interno per permettere la ricezione dei dati
        int result = recv(Client::sock, Client::receivingBuffer, sizeof(Client::receivingBuffer), 0);
        // viene verificato che non siano insorti errori durante la ricezione dei dati
        if (result == SOCKET_ERROR) {
            printWSAError(new char[]{
                    "Errore durante la ricezione dei dati."
            });
            closesocket(Client::sock);
            return nullptr;
        } else {
            std::cout << "Byte ricevuti: " << result << std::endl;
            std::cout << "Dati ricevuti:" << std::endl << Client::receivingBuffer << std::endl;
            std::cout << "> Fine ricezione <" << std::endl;
        }
        return Client::receivingBuffer;
    }

    /**
     * Metodo utilizzato per ottenere l'indirizzo ip del client
     * @return Sequenza di caratteri che identificano l'indirizzo ip del client
     */
    char *Client::getIp() {
        char *str = (char *) malloc(sizeof(char) * INET_ADDRSTRLEN);
        InetNtop(AF_INET, &(Client::clientAddr.sin_addr), str, INET_ADDRSTRLEN);
        return str;
    }

    /**
     * Metodo utilizzato per chiudere il socket.
     */
    void Client::close() const {
        closesocket(Client::sock);
    }


} // Socket