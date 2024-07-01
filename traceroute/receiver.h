//Pawel Richert 324903
#ifndef RECEIVER_H
#define RECEIVER_H

#include "utils.h"

bool receivePing(uint8_t* buffer, int ping_sockfd);

bool parseICMP(uint8_t *buffer, uint16_t expectedSeq,uint16_t expectedID, int& type, std::set<std::string>& ipAddr);

void PrintResponse(int packetCounter, std::set<std::string> stringAddr, uint16_t timeSum, int seqNo);

#endif