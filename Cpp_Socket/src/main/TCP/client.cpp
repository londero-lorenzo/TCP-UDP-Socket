//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client TCP
#include "../../TCP/Client.h"
// viene incluso il file cpp contenente le funzioni per elaborare gli argomenti passati al programma in fase d'avvio
#include "../../utils/Arguments.cpp"


/**
 * Blocco principale per l'esecuzione del programma lato Client TCP.
 * @param argc Numero di argomenti passati all'avvio dell'applicazione
 * @param argv Stringhe di argomenti passati all'avvio dell'applicazione
 */
int main(int argc, char *argv[]) {
    char *ip = nullptr, *stringToSend = nullptr;
    int port = -1;

    /*
    * ---------Inizializzazione variabili utili per il funzionamento del server---------
    */
    // viene controllato il numero di argomenti passati al programma
    if (argc == 1) {
        //(la prima posizione di argv contiene il nome del programma, quindi è scartabile)
        // viene utilizzato l'indirizzo ip di default
        ip = new char[]{
                "192.168.178.134"
        };
        // viene utilizzata la porta di default
        port = 5500;

        // viene utilizzata una stringa di default da inviare
        stringToSend = new char[]{
                "Ciao mondo!"
        };
    } else
        // per ogni argomento passato al programma, vengono inizializzate le variabili utili per la connessione al server
        for (int i = 0; i < argc; i++)
            setNetworkValuesFromArgument(&argv[i], &ip, &port, &stringToSend);
    // se almeno una delle variabili utili per instaurare una connessione con il server non viene inizializzata, viene lanciato un messaggio d'errore
    if (ip == nullptr || stringToSend == nullptr || port < 0)
        printErrorWithExit(new char[]{
                "Errore durante l'inizializzazione delle variabili per la connessione al server!"
        });

    /*
     * ---------Istruzioni per la comunicazione con il server---------
     */
    // viene creato l'oggetto client
    Socket::TCP::Client client;

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
