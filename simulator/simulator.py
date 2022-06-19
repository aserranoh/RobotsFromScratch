#!/usr/bin/env python

import socket
import sys

import tornado.ioloop
import tornado.web

class EventsHandler(tornado.web.RequestHandler):

    def initialize(self, sock):
        self.sock = sock
        self.set_header('content-type', 'text/event-stream')
        self.set_header('cache-control', 'no-cache')

    async def get(self):
        while True:
            data, addr = await tornado.ioloop.IOLoop.current().run_in_executor(
                None, sock.recvfrom, 1024)
            data = data[1:-1]
            self.write(f'data: {data.decode("ascii")}\n\n')
            await self.flush()

if __name__ == "__main__":
    http_port = int(sys.argv[1])
    udp_port = int(sys.argv[2])

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('0.0.0.0', udp_port))

    app = tornado.web.Application([
        (r'/', tornado.web.RedirectHandler, {'url': '/main.html'}),
        (r'/(main.html)', tornado.web.StaticFileHandler, {'path': '.'}),
        (r'/events', EventsHandler, {'sock': sock})
    ])
    app.listen(http_port)
    tornado.ioloop.IOLoop.current().start()

