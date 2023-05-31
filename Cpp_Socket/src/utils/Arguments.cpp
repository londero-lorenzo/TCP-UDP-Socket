//
// Created by Londero Lorenzo on ~ April 2023.
//

#include <string>
#include "Error.cpp"

#define UNRECOGNISED_ARG (-1)
#define ADDRESS_ARG 0
#define PORT_ARG 1
#define DATA_ARG 2
#define RAW_DATA_ARG 3


char delimiter = '-';
char addressDelimiter = 'a';
char portDelimiter = 'p';
char dataDelimiter = 'd';


int getArgumentType(const char *arg) {
    if (arg[0] != delimiter) return DATA_ARG;
    if (arg[1] == addressDelimiter) return ADDRESS_ARG;
    if (arg[1] == portDelimiter) return PORT_ARG;
    if (arg[1] == dataDelimiter) return RAW_DATA_ARG;
    return UNRECOGNISED_ARG;
}


char *removeDelimitersFromArgument(char *arg) {
    return (arg += 2);
}

char *getAddressFromArgument(char *arg) {
    return removeDelimitersFromArgument(arg);
}

int getPortFromArgument(char *arg) {
    int port;
    int result = sscanf_s(removeDelimitersFromArgument(arg), "%d", &port);

    if (result && std::to_string(port).length() == sizeof(arg))
        return port;
    else
        printError(new char[]{
                "Impossibile identificare la porta inserita!"
        });
    return -1;

}

char *getDataToSendFromArgument(char *arg) {
    return removeDelimitersFromArgument(arg);
}

void setNetworkValuesFromArgument(char **arg, char **ip, int *port, char **stringToSend) {
    int argument = getArgumentType(*arg);
    if (argument == ADDRESS_ARG)
        *ip = getAddressFromArgument(*arg);
    else if (argument == PORT_ARG)
        *port = getPortFromArgument(*arg);
    else if (argument == DATA_ARG)
        *stringToSend = *arg;
    else if (argument == RAW_DATA_ARG)
        *stringToSend = getDataToSendFromArgument(*arg);
}

void
initializeClientNetworkValuesFromArguments(const int *argc, char ***argv, char **ip, int *port, char **stringToSend) {
    /*
    * ---------Inizializzazione variabili utili per il funzionamento del server---------
    */
    // viene controllato il numero di argomenti passati al programma
    if (*argc == 1) {
        //(la prima posizione di argv contiene il nome del programma, quindi è scartabile)
        // viene utilizzato l'indirizzo ip di default
        *ip = new char[]{
                "192.168.178.134"
        };
        // viene utilizzata la porta di default
        *port = 5500;

        // viene utilizzata una stringa di default da inviare
        *stringToSend = new char[]{
                "Ciao mondo!"
        };
    } else
        // per ogni argomento passato al programma, vengono inizializzate le variabili utili per la connessione al server
        for (int i = 0; i < *argc; i++)
            setNetworkValuesFromArgument(&argv[0][i], &ip[0], &port[0], &stringToSend[0]);
    // se almeno una delle variabili utili per instaurare una connessione con il server non viene inizializzata, viene lanciato un messaggio d'errore
    if (*ip == nullptr || *stringToSend == nullptr || *port < 0)
        printErrorWithExit(new char[]{
                "Errore durante l'inizializzazione delle variabili per la connessione al server!"
        });
}


void initializeServerNetworkValuesFromArguments(const int *argc, char ***argv, int *port) {
    /*
     * ---------Inizializzazione variabili utili per il funzionamento del server---------
     */
    // viene controllato il numero di argomenti passati al programma
    if (*argc == 1) {
        // (la prima posizione di argv contiene il nome del programma, quindi è scartabile)
        // viene utilizzata la porta di default
        *port = 5500;
    } else {
        // viene controllato che l'argomento passato corrisponda alla porta a cui aprire il server
        int argument = getArgumentType(&argv[0][1][0]);
        if (argument == PORT_ARG || argument == DATA_ARG)
            *port = getPortFromArgument(&argv[0][1][0]);
    }
    // se la porta non è stata inizializzata, viene rilasciato un messaggio d'errore
    if (*port < 0)
        printErrorWithExit(new char[]{
                "Errore durante l'inizializzazione delle variabili per la connessione al server!"
        });
}