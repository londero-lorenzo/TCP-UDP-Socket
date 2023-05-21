//
// Created by Londero Lorenzo on ~ April 2023.
//

#include <Winsock2.h>
#include <WS2tcpip.h>

char *getMyIp() {
    char szBuffer[1024];

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if (::WSAStartup(wVersionRequested, &wsaData) != 0)
        return nullptr;


    if (gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR) {
        WSACleanup();
        return nullptr;
    }

    struct addrinfo *res;

    GetAddrInfoW((PCWSTR) (&szBuffer), nullptr, nullptr, (PADDRINFOW *) (&res));
    char *str = (char *) malloc(sizeof(char) * INET_ADDRSTRLEN);
    InetNtop(AF_INET, &(((struct sockaddr_in *) (res->ai_addr))->sin_addr), str, INET_ADDRSTRLEN);
    return str;
}