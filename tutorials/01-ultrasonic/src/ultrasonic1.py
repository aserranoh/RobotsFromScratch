#!/usr/bin/env python

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GLib
import math
import serial
import threading

SPEED_OF_SOUND = 343

class UltrasonicView(object):
    '''Widget to view the ultrasonic sensor.'''

    def __init__(self):
        self.value = 0
        self.window = Gtk.Window()
        self.window.connect("destroy", Gtk.main_quit)

        # Layout
        self.box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)
        self.window.add(self.box)

        # Drawing area
        self.darea = Gtk.DrawingArea()
        self.darea.set_size_request(512, 512);
        self.darea.connect("draw", self.on_draw)
        self.box.pack_start(self.darea, False, False, 0)

        # Label with the distance value
        self.label = Gtk.Label("Distance: ")
        self.box.pack_start(self.label, False, False, 0)

        self.window.show_all()

    def update(self, value):
        GLib.idle_add(self.set_value, value)

    def set_value(self, value):
        self.distance = (value * 0.000004) / 2 * SPEED_OF_SOUND
        self.label.set_markup(
            '<span font_size="40000">Distance: {:.3f} m</span>'.format(self.distance))
        self.darea.queue_draw()

    def torad(self, a):
        return a * math.pi / 180.0

    def on_draw(self, widget, cr):
        A = self.torad(30)
        R = 500
        O = (256, 512)
        cr.set_source_rgb(0, 0, 0)
        cr.paint()
        cr.set_source_rgb(1, 1, 1)
        cr.move_to(*O)
        cr.line_to(O[0], O[1] - R)
        cr.stroke()
        cr.move_to(*O)
        cr.line_to(O[0] - (math.sin(A) * R),
                   O[1] - (math.cos(A) * R))
        cr.stroke()
        cr.move_to(*O)
        cr.line_to(O[0] + (math.sin(A) * R),
                   O[1] - (math.cos(A) * R))
        cr.stroke()
        cr.arc(*O, R, -math.pi/2 - A, -math.pi/2 + A)
        cr.stroke()
        cr.arc(*O, R/2.0, -math.pi/2 - A, -math.pi/2 + A)
        cr.stroke()

        # Draw the value
        cr.set_source_rgb(1, 0, 0)
        cr.set_line_width(5)
        r = R * self.distance / 2
        cr.arc(*O, r, -math.pi/2 - A, -math.pi/2 + A)
        cr.stroke()

class SerialPort(threading.Thread):
    '''Receives data from the serial port.'''

    def __init__(self, listener):
        threading.Thread.__init__(self)
        self.listener = listener
        self.stopped = False
        self.start()

    def stop(self):
        self.stopped = True

    def run(self):
        with serial.Serial('/dev/ttyACM0', 19200, timeout=1) as s:
            while not self.stopped:
                try:
                    value = int(s.readline().strip())
                    self.listener.update(value)
                except ValueError:
                    pass
                

if __name__ == '__main__':
    u = UltrasonicView()
    s = SerialPort(u)    
    Gtk.main()
    s.stop()
    s.join()

