//
// Created by Londero Lorenzo on ~ April 2023.
//

// viene incluso il file header contenente le dichiarazioni del Client TCP
#include "../../TCP/Server.h"


// viene definito il blocco principale del programma lato Client TCP
int main() {

    // viene impostata la porta alla viene aperto il server
    int port = 5500;

    // viene creato l'oggetto server
    Socket::TCP::Server server;

    // viene avviato il servizio del server
    server.start(port);

    // viene chiuso il socket server
    server.close();
    return 0;
}