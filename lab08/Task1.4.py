#!/usr/bin/python3

from scapy.all import *

def spoof(pkt):
	if ICMP in pkt and pkt[ICMP].type == 8:
		print("Sniffed echo request from " + pkt[IP].src + " to " + pkt[IP].dst)
		ip = IP(src=pkt[IP].dst, dst=pkt[IP].src, ihl=pkt[IP].ihl)
		icmp = ICMP(type=0, id=pkt[ICMP].id, seq=pkt[ICMP].seq)
		newpkt = ip/icmp
		send(newpkt)
		print("sent echo response as " + newpkt[IP].src + " to " + newpkt[IP].dst)

sniff(filter="icmp and src host 10.0.2.15", prn=spoof)
