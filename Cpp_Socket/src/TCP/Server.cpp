//
// Created by Londero Lorenzo on ~ April 2023.
//

// vengono incluse le librerie utili per il funzionamento del socket
#include "Server.h"
#include "Client.h"
#include <Winsock2.h>
#include <string>

// viene incluso il file cpp utilizzato per mostrare a schermo gli errori insorti durante l'esecuzione del programma
#include "../utils/Error.cpp"

// viene aggiunta la libreria "ws2_32.lib" alla lista delle librerie utili per il funzionamento del socket
#pragma comment(lib, "ws2_32.lib")

// viene definito lo spazio logico nel quale si troverà l'oggetto di seguito definito
/**
 * Spazio logico nel quale sono racchiusi tutti gli oggetti Socket
 */
namespace Socket::TCP {

    /**
      * Costruttore pubblico generico, si occupa dell'inizializzazione dell'oggetto socket
      */
    Server::Server() {
        // viene caricata la struttura contenente le informazioni per l'implementazione dei Socket in Windows
        int result = WSAStartup(MAKEWORD(2, 2), &(Server::wsaData));
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
        Server::listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        // viene verificato che l'oggetto socket creato sia valido
        if (Server::listenSock == INVALID_SOCKET) {
            printWSAError(new char[]{
                    "Errore durante il caricamento del socket."
            });
            return;
        }
    }

    /**
     * Metodo utilizzato per permettere al socket di essere raggiungibile da una data porta
     * @param port Numero di porta alla quale il server sarà raggiungibile
     */
    void Server::start(int port) {
        // vengono impostati i parametri per permettere la connessione
        Server::serverAddr.sin_addr.s_addr = INADDR_ANY; // qualsiasi indirizzo i<p
        Server::serverAddr.sin_port = htons(port);
        Server::serverAddr.sin_family = AF_INET;
        // viene richiamato il metodo interno per permettere al socket di essere raggiunto alla data porta
        int result = bind(listenSock, (struct sockaddr *) (&serverAddr), sizeof(serverAddr));
        // viene verificato che non siano insorti errori
        if (result == SOCKET_ERROR) {
            std::string outputStringError =
                    "\nErrore durante l'apertura della porta :" + std::to_string(port);
            printWSAError(outputStringError.data());
            closesocket(Server::listenSock);
            return;
        }

        // inizio ascolto delle connessioni in entrata
        if (Server::listen() == SOCKET_ERROR) return;

        // creazione dell'oggetto client lato server per comunicare con il socket connesso
        Socket::TCP::Client client(&(Server::listenSock));
        // viene richiamato il metodo per la ricezione dei messaggi in arrivo dal client
        char *data = client.receive();
        // viene inviato lo stesso messaggio al client
        client.send(data);
        //viene chiusa la comunicazione
        client.close();
    }

    /**
     * Metodo utilizzato per mettere il server in ascolto alla porta selezionata
     * @return 0 se non insorgono errori altrimenti -1
     */
    int Server::listen() const {
        std::cout << "In attesa di una connessione ..." << std::endl;

        int result = ::listen(Server::listenSock, SOMAXCONN);
        if (result == SOCKET_ERROR) {
            std::string outputStringError =
                    "\nErrore durante l'ascolto alla porta :" + std::to_string(Server::getPort());
            printWSAError(outputStringError.data());
            closesocket(Server::listenSock);
        }
        return result;
    }

    /**
     * Metodo utilizzato per ottenere la porta alla quale il server è raggiungibile
     * @return Numero di porta alla quale i client si possono connettere
     */
    int Server::getPort() const {
        return Server::serverAddr.sin_port;
    }

    /**
     * Metodo utilizzato per chiudere il socket.
     */
    void Server::close() const {
        closesocket(Server::listenSock);
    }
}
