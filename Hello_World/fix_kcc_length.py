#! /usr/bin/env python3

"""
KCC-Dateien sollten eine Länge haben, die durch 128 teilbar ist
(= ganze 128 Byte-Blöcke)
"""

import sys

filename = sys.argv[1]

# einlesen
with open( filename, 'rb') as f_in:
    data = bytearray( f_in.read())

# ergänzen
count = 0
while( len( data) % 128 != 0):
    data.append( 0xff)
    count += 1


# ausgeben
with open( filename, 'wb') as f_out:
    f_out.write( bytes( data))

print( "%s: %s enhanced by %d bytes." % ( sys.argv[0], filename, count))
