//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client UDP
#include "../../UDP/Client.h"


// viene definito il blocco principale del programma lato Client TCP
int main() {

    // viene dichiarato e definito l'indirizzo IP del server al quale ci si vuole connettere
    char *ip = new char[]{
            "192.168.178.134"
    };
    // viene impostata la porta alla quale connettersi
    int port = 5500;

    // viene dichiarato e definito il messaggio da inviare al server
    char *stringToSend = new char[]{
            "Ciao mondo!"
    };

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
