#!/usr/bin/python

import sys, socket

if len(sys.argv)< 2 or sys.argv[1] == '-h' or sys.argv[1] == '--help':
  print 'Usage:', sys.argv[0], '<list of IP addresses>'
  exit(0)

i = 1
# iterate for all ips
print '<IP address>    \t\t<hostname>'
while i < len(sys.argv):
  hostname = socket.gethostbyaddr(sys.argv[i])
  print sys.argv[i], '\t\t',hostname[0]
  i += 1
