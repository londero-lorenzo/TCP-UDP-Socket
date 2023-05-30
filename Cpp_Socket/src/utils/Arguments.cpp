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

void setNetworkValuesFromArgument(char **arg, char **ip, int *port, char **stringToSend)
{
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