//
// Created by Londero Lorenzo on ~ April 2023.
//

#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <WinDNS.h>
#pragma comment(lib, "Dnsapi.lib")

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

    PDNS_RECORD pDnsRecord;

    DNS_STATUS status = DnsQuery(szBuffer, DNS_TYPE_A, DNS_QUERY_STANDARD, NULL, &pDnsRecord, NULL);


    char *str = (char *) malloc(sizeof(char) * INET_ADDRSTRLEN);
    InetNtop(AF_INET, &(((struct sockaddr_in *) (pDnsRecord))->sin_addr), str, INET_ADDRSTRLEN);
    return str;
}