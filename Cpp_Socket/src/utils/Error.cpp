//
// Created by londe on 30/05/2023.
//
#include <Winsock2.h>
#include <iostream>

/**
 * Funzione utilizzata per stampare a schermo un errore generico.
 * @param description Descrizione dell'errore
 */
static void printError(char *description) {
    std::cerr << description << std::endl;
}

/**
 * Funzione utilizzata per stampare a schermo un errore che impone un interruzione del programma.
 * @param description Descrizione dell'errore
 */
static void printErrorWithExit(char *description)
{
    std::cerr << description << std::endl;
    exit(-1);
}

/**
 * Funzione utilizzata per stampare a schermo gli eventuali errori generati durante l'esecuzione del programma.
 * @param description Descrizione dell'errore
 */
static void printWSAError(char *description) {
    printError(description);
    std::cerr << "Codice d'uscia: " << WSAGetLastError() << std::endl;
    WSACleanup();
}

/**
 * Funzione alternativa utilizzata per stampare a schermo gli eventuali errori generati durante l'esecuzione del programma prima del caricamento di WSAStartup.
 * @param description Descrizione dell'errore
 * @param exitCode Codice d'uscita nel momento del caricamento di WSAStartup
 */
static void printErrorBeforeWSAInit(char *description, int exitCode) {
    std::cerr << description << std::endl;
    std::cerr << "Codice d'uscia: " << exitCode << std::endl;
}
