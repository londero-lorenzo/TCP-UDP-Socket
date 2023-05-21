//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client UDP
#include "../../UDP/Server.h"


// viene definito il blocco principale del programma lato Client UDP
int main() {

    // viene impostata la porta alla viene aperto il server
    int port = 5500;

    // viene creato l'oggetto server
    Socket::UDP::Server server;

    // viene avviato il servizio del server
    server.start(port);

    // viene chiuso il socket server
    server.close();
    return 0;
}