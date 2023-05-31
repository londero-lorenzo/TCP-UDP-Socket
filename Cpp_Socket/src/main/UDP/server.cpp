//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client UDP
#include "../../UDP/Server.h"
// viene incluso il file cpp contenente le funzioni per elaborare gli argomenti passati al programma in fase d'avvio
#include "../../utils/Arguments.cpp"


/**
 * Blocco principale per l'esecuzione del programma lato Server UDP.
 * @param argc Numero di argomenti passati all'avvio dell'applicazione
 * @param argv Stringhe di argomenti passati all'avvio dell'applicazione
 */
int main(int argc, char *argv[]) {
    int port = -1;

    // vengono inizializzati i parametri per permettere il funzionamento del server
    initializeServerNetworkValuesFromArguments(&argc, &argv, &port);

    /*
     * ---------Istruzioni per l'avvio del server---------
     */
    // viene creato l'oggetto server
    Socket::UDP::Server server;

    // viene avviato il servizio del server
    server.start(port);

    // viene chiuso il socket server
    server.close();
    return 0;
}