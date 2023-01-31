#include <iostream>
#include <cstdlib>
#include "server.h"
#include "dns_message.h"

using namespace std;

Server* serv = new Server();
struct sockaddr_in from;
socklen_t from_size = sizeof(from);

int main()
{
    int iError = 0;

    iError = serv->CreateConnection();
    if (iError != 0)
    {
        exit(EXIT_FAILURE);
    }

    int i  = 0;
    size_t sz = 512*sizeof(char);
    while (1)
    {
        char* pcMsg = (char*) malloc(sz);
        int bytesRCV = recvfrom(serv->GetSocket(), pcMsg, sz, 0, (struct sockaddr *) &from, &from_size);
        if (bytesRCV < 0){
            printf("Error: %s\n", strerror(errno));
            close(serv->GetSocket());
            return 0;
            continue;
        }
        char* ip_host = (char*)malloc(15);
        inet_ntop(AF_INET, &(from.sin_addr), ip_host,15);
        printf("Message from: %s, size: %d\n", ip_host, bytesRCV);
        printf("\n");
        dns_message msg = dns_message();
        msg.processHeader(pcMsg);
        msg.printHeader();
        msg.processQuestion(pcMsg);
        i++;
        if (i > 50)
        {
            close(serv->GetSocket());
            return 0;
        }

    }
}
