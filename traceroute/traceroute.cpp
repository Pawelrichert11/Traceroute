//Pawel Richert 324903
#include "utils.h"
#include "sender.h"
#include "receiver.h"
void setupDestAddress(sockaddr_in& destAddr, const char* target) {
  struct hostent *host = gethostbyname(target);
  if (host == NULL){
    cerr << "Niepoprawny adres IP" << endl;
    exit(1);
  }
  destAddr.sin_addr.s_addr = *(long*)(host->h_addr);
  destAddr.sin_family = AF_INET;
  destAddr.sin_port = 0;
}
int createSocket() {
  int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sockfd < 0) {
    cerr << "Blad utworzenia gniazda" << endl;
    exit(1);
  }
  return sockfd;
}
int sendTriplet(int sockfd, struct sockaddr_in *pingAddr, unsigned int ttl, unsigned int seqNo)
{
  uint8_t buffer[PACKET_SIZE];
  memset(buffer, 0, PACKET_SIZE);
  std::set<string> stringAddr;
  int packetType, packetCounter = 0;
  uint16_t timeSum = 0;

  fd_set readFds; 
  struct timeval time;
  time.tv_sec = 0;
  FD_ZERO(&readFds);
  FD_SET(STDIN_FILENO, &readFds);
  FD_SET(sockfd, &readFds); 

  for (int i=0;i<3;i++) send(sockfd,seqNo,ttl,pingAddr);

  while (packetCounter < 3) {
    time.tv_usec = PING_SLEEP_RATE - timeSum;

    auto start = high_resolution_clock::now();

    int ready = select(sockfd + 1, &readFds, NULL, NULL, &time);

    auto stop = high_resolution_clock::now();
    timeSum += duration_cast<microseconds>(stop - start).count();

    if (ready <= 0) {
      break;
    }
    else if (ready>0) {
      uint16_t id = getpid() & 0xFFFF;
      if(receivePing(buffer,sockfd) &&
      parseICMP(buffer,seqNo,id, packetType, stringAddr))
      {
        packetCounter++;
      }
    }
  }
  PrintResponse(packetCounter, stringAddr, timeSum, seqNo);
    if(packetType == ICMP_ECHOREPLY)
    {
      return WE_GOT_ECHO_REPLY;
    }
    return 0;
}
int main(int argc, char *argv[]) {
  struct sockaddr_in destAddr;

  if (argc != 2)
  {
    cerr << "Niepoprawny adres IP" << endl;
  }

  const char *target = argv[1];
  setupDestAddress(destAddr,target);

  int sockfd = createSocket();
  for(int ttl=1;ttl<=30;ttl++)
  {
    if(sendTriplet(sockfd,
              &destAddr,
              ttl,
              ttl) == WE_GOT_ECHO_REPLY)
    {
      break;
    }
  }
  close(sockfd);
  return 0;
}