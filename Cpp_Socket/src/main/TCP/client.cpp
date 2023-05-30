//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client TCP
#include "../../TCP/Client.h"
#include "../../utils/Arguments.cpp"


// viene definito il blocco principale del programma lato Client TCP
int main(int argc, char *argv[]) {
    char *ip, *stringToSend;
    int port;
    if (argc == 1) {
        // viene dichiarato e definito l'indirizzo IP del server al quale ci si vuole connettere
        ip = new char[]{
                "192.168.178.134"
        };
        // viene impostata la porta alla quale connettersi
        port = 5500;

        // viene dichiarato e definito il messaggio da inviare al server
        stringToSend = new char[]{
                "Ciao mondo!"
        };
    } else
        for (int i = 0; i < argc; i++)
            setNetworkValuesFromArgument(&argv[i], &ip, &port, &stringToSend);
    if (ip == nullptr || stringToSend == nullptr || port < 0)
        printErrorWithExit(new char[]{
                "Errore durante l'inizializzazione delle variabili per la connessione al server!"
        });


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
