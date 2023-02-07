//
// Created by Dominika Bobik on 2/6/23.
//

#include <netinet/in.h>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <arpa/inet.h>

#ifndef DNSTEST_CLIENT_H
#define DNSTEST_CLIENT_H

#define EXTERNAL_SERVER_IP "8.8.8.8"
#define PORT 53

using namespace std;

class client {
public:
    int socket_fd;
    struct sockaddr_in from{};
    socklen_t from_size;
    client();
    int createConnection();
    int getSocket();
};

#endif //DNSTEST_CLIENT_H

