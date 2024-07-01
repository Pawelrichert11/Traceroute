//Pawel Richert 324903
#ifndef SENDER_H
#define SENDER_H

#include "utils.h"

unsigned short checkSum(void *buffer, int length);

void setICMPheader(struct icmpheader &icmp, int seqNo);

void send(int ping_sockfd, int seqNo, int ttl, struct sockaddr_in *ping_addr);

#endif