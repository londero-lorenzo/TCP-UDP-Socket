//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client UDP
#include "../../UDP/Client.h"
// viene incluso il file cpp contenente le funzioni per elaborare gli argomenti passati al programma in fase d'avvio
#include "../../utils/Arguments.cpp"

/**
 * Blocco principale per l'esecuzione del programma lato Client UDP.
 * @param argc Numero di argomenti passati all'avvio dell'applicazione
 * @param argv Stringhe di argomenti passati all'avvio dell'applicazione
 */
int main(int argc, char *argv[]) {
    char *ip = nullptr, *stringToSend = nullptr;
    int port = -1;

    // vengono inizializzati i parametri per permettere la connessione al server
    initializeClientNetworkValuesFromArguments(&argc, &argv, &ip, &port, &stringToSend);

    /*
     * ---------Istruzioni per la comunicazione con il server---------
     */
    // viene creato l'oggetto client
    Socket::UDP::Client client;

    // viene passato al metodo i parametri per permettere la connessione al server
    client.connectTo(ip, port);

    // viene inviato il messaggio al server
    client.send(stringToSend);

    // viene richiamato il metodo per la ricezione dei messaggi in arrivo dal server
    client.receive();

    // viene chiuso il socket client
    client.close();
    return 0;
}
