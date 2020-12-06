#!/usr/bin/python3

import sys
from scapy.all import *

a = IP()
a.dst = "8.8.8.8"
a.src = sys.argv[1]	#get an arbitrary source from command line
b = ICMP()
p = a/b 	#add b as the IP payload
p.show()	#Display packet info showing our arbitrary source
send(p)		#Send the packet