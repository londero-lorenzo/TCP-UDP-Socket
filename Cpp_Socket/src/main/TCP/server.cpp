//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client TCP
#include "../../TCP/Server.h"
// viene incluso il file cpp contenente le funzioni per elaborare gli argomenti passati al programma in fase d'avvio
#include "../../utils/Arguments.cpp"


/**
 * Blocco principale per l'esecuzione del programma lato Server TCP.
 * @param argc Numero di argomenti passati all'avvio dell'applicazione
 * @param argv Stringhe di argomenti passati all'avvio dell'applicazione
 */
int main(int argc, char *argv[]) {
    int port = -1;

    /*
     * ---------Inizializzazione variabili utili per il funzionamento del server---------
     */
    // viene controllato il numero di argomenti passati al programma
    if (argc == 1) {
        // (la prima posizione di argv contiene il nome del programma, quindi è scartabile)
        // viene utilizzata la porta di default
        port = 5500;
    } else {
        // viene controllato che l'argomento passato corrisponda alla porta a cui aprire il server
        int argument = getArgumentType(argv[1]);
        if (argument == PORT_ARG || argument == DATA_ARG)
            port = getPortFromArgument(argv[1]);
    }
    // se la porta non è stata inizializzata, viene rilasciato un messaggio d'errore
    if (port < 0)
        printErrorWithExit(new char[]{
                "Errore durante l'inizializzazione delle variabili per la connessione al server!"
        });

    /*
     * ---------Istruzioni per l'avvio del server---------
     */
    // viene creato l'oggetto server
    Socket::TCP::Server server;

    // viene avviato il servizio del server alla porta indicata
    server.start(port);

    // viene chiuso il socket server
    server.close();
    return 0;
}