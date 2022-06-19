#!/usr/bin/env python3

import socket
import sys

in_port = int(sys.argv[1])
dst_address = sys.argv[2]
out_port = int(sys.argv[3])

in_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
in_sock.bind(('0.0.0.0', in_port))

out_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    data, addr = in_sock.recvfrom(1024)
    data = data.decode('ascii')
    if not data.startswith(':') or not data.endswith('\n'):
        print(f'wrong message received {data}', file=sys.stderr)
        continue
    fields = data[1:-1].split(',')
    if len(fields) != 2:
        print(f'wrong message received {data}', file=sys.stderr)
        continue
    try:
        x, y = int(fields[0]), int(fields[1])
        speed = int(y * 255 / 100)
        turn = int(x * 255 / 100)
        msg = f':mv,{speed},{turn}\n'
        out_sock.sendto(msg.encode('ascii'), (dst_address, out_port))
    except ValueError:
        print(f'wrong message received {data}', file=sys.stderr)

