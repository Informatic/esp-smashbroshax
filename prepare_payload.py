#!/usr/bin/env python

from __future__ import print_function

import sys
import os

if len(sys.argv) != 2:
    print('usage: %s [pcap file] > app/payload.h' % sys.argv[0], file=sys.stderr)
    exit(1)

pcap_name = sys.argv[1]
print('// Generated payload for %s' % os.path.basename(pcap_name))

pcap = open(pcap_name).read()

print('uint8_t payload[] = {\n   ',)
for i, c in enumerate(pcap[58:]):
    print('0x%02x,' % ord(c),)

    if i % 24 == 23:
        print('\n   ',)


print('\n};')

print('uint16_t payload_size = %d;' % len(pcap[58:]))
