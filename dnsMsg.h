//
// Created by Dominika Bobik on 1/28/23.
//

#ifndef DNS_DNS_HEADER_H
#define DNS_DNS_HEADER_H

#include <cstdint>

#define MAX_LABEL_SIZE 63
#define MAX_NAME_SIZE 255
#define MAX_UDP_MSG_SIZE 512

enum rcode {
    no_error = 0,
    format_error = 1,
    server_failure = 2,
    name_error = 3,
    not_implemented = 4,
    refused = 5
};

enum op_code {
    query = 0,
    iquery = 1,
    status = 2
};

class dnsMsg {
public:
    dnsMsg();
    u_int16_t id = 0;
    u_int8_t qr = 0;
    u_int8_t opcode = 0;
    u_int8_t aa = 0;
    u_int8_t tc = 0;
    u_int8_t rd = 0;
    u_int8_t ra = 0;
    u_int8_t z = 0;
    u_int8_t rcode = 0;
    u_int16_t qd_count = 0;
    u_int16_t an_count = 0;
    u_int16_t ns_count = 0;
    u_int16_t ar_count = 0;
    int processHeader(char* buff);
    int processQuestion(char* buff);
    void printQuestion() const;
    void printHeader() const;
};

#endif //DNS_DNS_HEADER_H