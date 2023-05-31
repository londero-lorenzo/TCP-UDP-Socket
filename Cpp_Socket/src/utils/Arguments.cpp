//
// Created by Londero Lorenzo on ~ April 2023.
//

#include <string>
#include "Error.cpp"

// vengono definiti degli identificatori atti a riconoscere il tipo di argomento passato all'avvio del programma
#define UNRECOGNISED_ARG (-1)
#define ADDRESS_ARG 0
#define PORT_ARG 1
#define DATA_ARG 2
#define RAW_DATA_ARG 3

// delimitatore standard
char delimiter = '-';
char addressDelimiter = 'a';
char portDelimiter = 'p';
char dataDelimiter = 'd';
/*
 * Possibili combinazioni:
 * *.exe -a192.168.120.33 -p5505 -d"Ciao Mondo!"
 * *.exe -a192.168.120.33 -p5505 "Ciao Mondo!"
 * *.exe
 *
 */

/**
 * Funzione utilizzata per riconoscere la tipologia a cui fa riferimento l'argomento passato come parametro.
 * @param arg Argomento passato all'avvio dell'applicazione
 * @return Identificatori di riconoscimento
 */
int getArgumentType(const char *arg) {
    if (arg[0] != delimiter) return DATA_ARG;
    if (arg[1] == addressDelimiter) return ADDRESS_ARG;
    if (arg[1] == portDelimiter) return PORT_ARG;
    if (arg[1] == dataDelimiter) return RAW_DATA_ARG;
    return UNRECOGNISED_ARG;
}

/**
 * Funzione utilizzata per mantenere solamente i dati utili dall'argomento passato come parametro.
 * @param arg Argomento passato all'avvio dell'applicazione
 * @return Sequenza di caratteri utili relativi alla tipologia d'argomento
 */
char *removeDelimitersFromArgument(char *arg) {
    return (arg += 2);
}

/**
 * Funzione utilizzata per ottenere l'indirizzo ip dall'argomento passato come parametro.
 * @param arg Argomento passato all'avvio dell'applicazione
 * @return Sequenza di caratteri contenente l'indirizzo ip
 */
char *getAddressFromArgument(char *arg) {
    return removeDelimitersFromArgument(arg);
}

/**
 * Funzione utilizzata per ottenere la porta alla quale opera il socket dall'argomento passato come parametro.
 * @param arg Argomento passato all'avvio dell'applicazione
 * @return Numero riferito alla porta alla quale dovrà operare il socket
 */
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

/**
 * Funzione utilizzata per ottenere i dati da trasmettere dall'argomento passato come parametro.
 * @param arg Argomento passato all'avvio dell'applicazione
 * @return Sequenza di caratteri contenente i dati da trasmettere
 */
char *getDataToSendFromArgument(char *arg) {
    return removeDelimitersFromArgument(arg);
}

/**
 * Funzione utilizzata per inizializzare le variabili passate come argomenti tramite le informazioni fornite durante l'avvio del programma.
 * @param arg Riferimento alla stringa contenente l'argomento passato all'avvio dell'applicazione
 * @param ip Riferimento alla stringa nella quale verrà immagazzinato l'indirizzo ip del socket
 * @param port Riferimento all'intero nel quale verrà immagazzinata la porta del socket
 * @param stringToSend Riferimento alla stringa nella quale verranno immagazzinate le informazioni da trasmettere
 */
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

/**
 * Funzione utilizzata per inizializzare automaticamente le variabili utili per permettere al Client di instaurare una comunicazione tramite gli argomenti passati durante l'avvio del programma.
 * @param argc Numero di argomenti passati all'avvio dell'applicazione
 * @param argv Stringhe di argomenti passati all'avvio dell'applicazione
 * @param ip Riferimento alla stringa nella quale verrà immagazzinato l'indirizzo ip del socket
 * @param port Riferimento all'intero nel quale verrà immagazzinata la porta del socket
 * @param stringToSend Riferimento alla stringa nella quale verranno immagazzinate le informazioni da trasmettere
 */
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

/**
 * Funzione utilizzata per inizializzare automaticamente le variabili utili per permettere al Server di instaurare una comunicazione tramite gli argomenti passati durante l'avvio del programma.
 * @param argc Numero di argomenti passati all'avvio dell'applicazione
 * @param argv Stringhe di argomenti passati all'avvio dell'applicazione
 * @param port Riferimento all'intero nel quale verrà immagazzinata la porta del socket
 */
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