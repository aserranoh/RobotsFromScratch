#!/usr/bin/env python

import os
import socket
import sys
import bottle

@bottle.route('/')
def root():
    return bottle.redirect('/main.html')

@bottle.route('/main.html')
def main():
    return bottle.template('main.html', color=os.environ['JOYSTICK_COLOR'])

@bottle.route('/joy.js')
def joy():
    return bottle.static_file('joy.js', root='.')

@bottle.route('/joystick-base.png')
def joy():
    return bottle.static_file('joystick-base.png', root='.')

@bottle.route('/position', method=['POST'])
def position():
    x = bottle.request.forms.get('x')
    y = bottle.request.forms.get('y')
    msg = f':{x},{y}\n'
    sock.sendto(msg.encode('ascii'), (dst_address, udp_port))

if __name__ == "__main__":
    http_port = int(sys.argv[1])
    dst_address = sys.argv[2]
    udp_port = int(sys.argv[3])
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    bottle.run(host='0.0.0.0', port=http_port, quiet=True)

