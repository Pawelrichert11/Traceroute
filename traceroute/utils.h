//Pawel Richert 324903
#ifndef ICMP_UTILS_H
#define ICMP_UTILS_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <cstring>
#include <cstdio>
#include <netinet/ip.h>
#include <iomanip>
#include <chrono>
#include "../../../../usr/include/netinet/ip_icmp.h"
#include <set>


using namespace std;
using namespace std::chrono;

const int PING_SLEEP_RATE = 1000000;  
const int PACKET_SIZE = 65535;
const int WE_GOT_ECHO_REPLY = 113;

struct icmpheader {
    unsigned char type;
    unsigned char code;
    unsigned short checkSum;
    unsigned short id;
    unsigned short seq;
    time_t timeStamp;
};
#endif