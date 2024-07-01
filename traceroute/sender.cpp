//Pawel Richert 324903
#include "sender.h"
unsigned short checkSum( void *buffer, int length ) {
  unsigned short *buff = (unsigned short*)buffer;
  unsigned int sum = 0;
  unsigned short result;
  for (sum = 0; length > 1; length -= 2)
  {
    sum += *buff++;
  }
  if (length == 1)
  {
    sum += *(unsigned char*)buff;
  }
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  result = ~sum;
  return result;
}
void setICMPheader(struct icmpheader& icmp, int seqNo)
{
  icmp.timeStamp = time(NULL);
  icmp.seq = seqNo;
  icmp.checkSum = 0;
  icmp.type = ICMP_ECHO;
  icmp.id = getpid() & 0xFFFF;
  icmp.code = 0;
  icmp.checkSum = checkSum(&icmp, sizeof(icmp));
}
void send(int ping_sockfd, int seqNo, int ttl, struct sockaddr_in *ping_addr)
{

  if (setsockopt(ping_sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) != 0)
  {
    cerr << "\nUstawianie TTL nie powiodlo sie\n";
    return;
  }
  struct icmpheader icmp;
  setICMPheader(icmp, seqNo);
  if (sendto(ping_sockfd, &icmp, sizeof(icmp), 0, (struct sockaddr*) ping_addr, sizeof(*ping_addr)) <= 0)
    {
      cerr << "\nWysylanie pakietu nie powiodlo sie\n";
    }
}