# Traceroute
The traceroute program is a tool designed to display the IP addresses of routers along the path to a target IP address. It allows users to trace the route packets take through a network, identifying each hop (router) they pass through before reaching their destination. 

# Implementation:
The program is implemented in C++, using raw sockets to send and receive ICMP (Internet Control Message Protocol) packets. Specifically, it sends ICMP Echo Request messages with incrementing TTL (Time to Live) values and listens for ICMP Time Exceeded messages to identify each hop. The program runs in text mode and takes a single argument: the target IP address.

# To run the program:
./traceroute <target_ip>
