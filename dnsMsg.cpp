//
// Created by Dominika Bobik on 1/28/23.
//

#include <cstdio>
#include "dnsMsg.h"

void dnsMsg::printHeader() const {
    printf("ID: %hu\n", id);
    printf("QR: %hu\n", qr);
    printf("OP code: %hu\n", opcode);
    printf("AA: %hu TC: %hu RD: %hu RA: %hu\n", aa, tc, rd, ra);
    printf("Z: %hu RCODE: %hu\n", z, rcode);
    printf("QDCOUNT: %hu, ANCOUNT %hu, NSCOUNT %hu, ARCOUNT %hu\n", qd_count, an_count, ns_count, ar_count);
}

int dnsMsg::processHeader(char *buff) {
    id = (buff[0] >> 8) | buff[1];
    qr = buff[2] & 0x80;
    opcode = (buff[2] >> 3) & 0xF;
    aa = (buff[2] >> 6) & 1;
    tc = (buff[2] >> 7) & 1;
    rd = buff[2] & 1;
    ra = (buff[3] >> 7) & 1;
    z = (buff[3] >> 4) & 0x7;
    rcode = buff[3] & 0xF;
    qd_count = (buff[4] >> 8) | buff[5];
    an_count = (buff[6] >> 8) | buff[7];
    ns_count = (buff[8] >> 8) | buff[9];
    ar_count = (buff[10] >> 8) | buff[11];
    return 0;
}



dnsMsg::dnsMsg() {

}

int dnsMsg::processQuestion(char *buff) {
    uint8_t label_length = buff[13];
    uint16_t qtype = 0;
    uint16_t qclass = 0;
    int i = 0;
    char name[label_length * 8];
    for (int i = 0; i < label_length; i++)
    {
        name[i] = buff[13 + i];
    }

    qtype = (buff[13 + i] >> 8) | buff[12 + i];
    qclass = (buff[15 + i] >> 8) | buff[14 + i];
    printf("NAME: %s\n", name);
    printf("QTYPE: %hu\n", qtype);
    printf("QCLASS: %x\n", qclass);
    return 0;
}

void dnsMsg::printQuestion() const {

}
