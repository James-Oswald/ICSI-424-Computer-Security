#!/usr/bin/python3

import sys
from scapy.all import *

print("Traceroute to " + sys.argv[1])
counter = 1
while True:
	a = IP()
	a.dst = sys.argv[1] #desination 
	a.ttl = counter
	result = sr1(a/ICMP(), verbose=False)	#send packet
	if result.type != 11: 		#11 is a time to live exceeded error code
		if result.type != 0:	#0 is the echo responce code
			raise "Unexpected ICMP responce code: " + str(result.type)
		print("Recived echo responce from " + result.src) 
		print("Traceroute passed through " + str(counter - 1) + " routers")
		break
	print("Router #" + str(counter) + ": " + result.src)
	counter = counter + 1

