//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client TCP
#include "../../TCP/Server.h"
#include "../../utils/Arguments.cpp"


// viene definito il blocco principale del programma lato Client TCP
int main(int argc, char *argv[]) {
    int port;
    if (argc == 1) {
        // viene impostata la porta alla viene aperto il server
        port = 5500;
    } else {
        int argument = getArgumentType(argv[2]);
        if (argument == PORT_ARG || argument == DATA_ARG)
            port = getPortFromArgument(argv[2]);
    }
    if (port < 0)
        printErrorWithExit(new char[]{
                "Errore durante l'inizializzazione delle variabili per la connessione al server!"
        });

    // viene creato l'oggetto server
    Socket::TCP::Server server;

    // viene avviato il servizio del server
    server.start(port);

    // viene chiuso il socket server
    server.close();
    return 0;
}