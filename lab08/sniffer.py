#!/usr/bin/python3

from scapy.all import *

def print_pkt(pkt):
	pkt.show()

pkt = sniff(filter='dst net 10.0.0.0/16', prn=print_pkt)