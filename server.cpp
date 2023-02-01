#include "server.h"

Server::Server()
{
    iSocketFd = 0;
    iServSize = sizeof(serv);
    bzero((char *) &serv, iServSize);
    iFromSize = sizeof(from);
    bzero((char *) &from, iFromSize);
}

int Server::CreateConnection()
{
    int iError = 0;

    iSocketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (iSocketFd == -1)
    {
        printf("Error while creating socket\n");
        iError = iSocketFd;
        return iError;
    }

    printf("Socket fd: %d\n", iSocketFd);
    bzero((char *) &serv, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    fflush(stdout);
    // Binding socket
    iServSize = sizeof(serv);
    iError = ::bind(iSocketFd, (struct sockaddr *) &serv, iServSize);
    if (iError < 0)
    {
        printf("Failed to bind the socket\n");
        close(iSocketFd);
        return iError;
    }

    printf("Server running\n");
    printf("Port:       %d (network byte order)\n", serv.sin_port);
    printf("            %d (hostorder)\n", PORT);
    printf("Domain:     AF_INET\n");
    printf("Protocol:   UDP\n\n");

    return iError;
}

int Server::GetSocket() {
    return iSocketFd;
}

