//Pawel Richert 324903
#include "receiver.h"
bool receivePing(uint8_t* buffer, int ping_sockfd)
{
  struct sockaddr_in r_addr;
  unsigned int addr_len = sizeof(r_addr);
  return !(recvfrom(ping_sockfd, buffer, PACKET_SIZE, 0,(struct sockaddr*)&r_addr, &addr_len) <= 0);
}
bool parseICMP(uint8_t *buffer, uint16_t expectedSeq, uint16_t expectedID, int& type, std::set<string>& ipAddr)
{  
  uint16_t id, seq; 
  struct ip *ipHdr = (struct ip*)buffer;
  ssize_t offset = sizeof(int32_t)*ipHdr->ip_hl;
  struct icmp* icmpValues = (struct icmp*)(buffer + offset);

  char ipStr[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(ipHdr->ip_src), ipStr, INET_ADDRSTRLEN);
  int localType = icmpValues->icmp_type;

  if (localType == ICMP_TIMXCEED) {
    offset = offset + 8;
    ipHdr = (struct ip *)(buffer + offset);
    offset = offset + sizeof(int32_t) * ipHdr->ip_hl;
    icmpValues = (struct icmp *)(buffer + offset);
  }
  if(localType == ICMP_ECHOREPLY or localType == ICMP_TIMXCEED)
  {
    id = icmpValues->icmp_id;
    seq = icmpValues->icmp_seq;
    if (expectedSeq == seq and expectedID == id) {
      ipAddr.insert(std::string(ipStr));
      type = icmpValues->icmp_type;
      return true;
    }
  }
  return false;
}
void PrintResponse(int packetCounter, set<string> stringAddr,uint16_t timeSum, int seqNo)
{
  cout<<seqNo<<". ";
  if(packetCounter == 0)
  {
    cout<<"*"<<endl;
  }
  else
  {
    for(string s : stringAddr)
    {
      cout<<s<<" ";
    }
    if(packetCounter == 3)
    {
      cout<<" "<<(timeSum/packetCounter)/1000<<" ms"<<endl;
    } 
    else
    {
      cout<<" ?"<<endl;
    }
  }
}