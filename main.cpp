#include <iostream>
#include <cstdlib>
#include "server.h"
#include "dnsMsg.h"
#include "client.h"

using namespace std;

#define MAX_MSG_SIZE 512
server* serv = new server();
client* cli = new client();

int main()
{
    int error = 0;
    error = serv->createConnection();
    if (error != 0)
    {
        printf("Server failed to connect\n");
        exit(EXIT_FAILURE);
    }


    size_t msg_size = MAX_MSG_SIZE * sizeof(char);
    while (1)
    {
        // Get new request from the client
        char* pcMsg = (char*) malloc(msg_size);
        int bytesRCV = recvfrom(serv->getSocket(), pcMsg, msg_size, 0, (struct sockaddr *) &serv->from, &serv->from_size);
        if (bytesRCV < 0){
            printf("Failed to recv msg Error: %s\n", strerror(errno));
            close(serv->getSocket());
            close(cli->getSocket());
            free(pcMsg);
            exit(1);
        }
        char* ip_host = (char*) malloc(15);
        inet_ntop(AF_INET, &(serv->from.sin_addr), ip_host,15);
        printf("Message from: %s, size: %d\n", ip_host, bytesRCV);
        printf("\n");
//        dnsMsg msg = dnsMsg();
//        msg.processHeader(pcMsg);
//        msg.printHeader();
//        msg.processQuestion(pcMsg);

        // Connect to the external server
        error = cli->createConnection();
        if (error != 0)
        {
            printf("Client failed to connect\n");
            exit(EXIT_FAILURE);
        }
        // Send request to the external server
        int bytesSNDExt = sendto(cli->getSocket(), pcMsg, bytesRCV, 0, (struct sockaddr *) &cli->from, cli->from_size);
        if (bytesSNDExt < 0){
            printf("Failed to send msg Error: %s\n", strerror(errno));
            close(serv->getSocket());
            close(cli->getSocket());
            free(pcMsg);
            free(ip_host);
            exit(1);
        }
        printf("Msg sent to external server %d bytes\n", bytesSNDExt);
        free(pcMsg);
        free(ip_host);

        // Get the response from the external server
        char* msgG = (char*) malloc(msg_size);
        int bytesRCVExt = recvfrom(cli->getSocket(), msgG, msg_size, 0, (struct sockaddr *) &cli->from, &cli->from_size);
        if (bytesRCVExt < 0){
            printf("Failed to recv msg Error: %s\n", strerror(errno));
            close(serv->getSocket());
            close(cli->getSocket());
            free(msgG);
            exit(1);
        }
        char* ip_host1 = (char*) malloc(15);
        inet_ntop(AF_INET, &(cli->from.sin_addr), ip_host1,15);
        printf("Message from: %s, size: %d\n", ip_host1, bytesRCVExt);

        // Close connection to the external server
        close(cli->getSocket());

        // Send response back to the client
        int bytesSND = sendto(serv->getSocket(), msgG, bytesRCVExt, 0, (struct sockaddr *) &(serv->serv), serv->serv_size);
        if (bytesSND < 0){
            printf("Failed to send msg Error: %s\n", strerror(errno));
            close(serv->getSocket());
            close(cli->getSocket());
            exit(1);
        }
        printf("\nMessage sent back to: %s, %d bytes\n", ip_host1, bytesSND);
        free(msgG);
        free(ip_host1);
        printf("----------\n");

    }
}
