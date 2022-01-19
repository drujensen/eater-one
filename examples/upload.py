#!/usr/bin/env python3

#stty -f /dev/tty.usbserial-1410 speed 9600 cs8 raw -igncr

import sys
import serial
import time

val = b''
ser = serial.Serial("/dev/cu.usbserial-210", 9600)
while val != b'>':
    val = ser.read()

with open(sys.argv[1], 'r') as my_file:
    for line in my_file:
        for ch in line:
            ser.write(ch.encode('latin-1'))
            time.sleep(0.1)
        ser.write(b"\x0D")
        time.sleep(1)

ser.close()
