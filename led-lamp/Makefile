
CFLAGS = -O2 -Wall --param=min-pagesize=0 -Wno-array-bounds
MCU = atmega328p
F = 16000000UL
PORT = /dev/ttyUSB0
BAUDS = 57600
PROGRAMMER = arduino

all: main.hex

main.o: main.c
	avr-gcc $(CFLAGS) -DF_CPU=$(F) -mmcu=$(MCU) -c -o $@ $<

main: main.o
	avr-gcc -mmcu=$(MCU) -o $@ $< -lrfsavr

main.hex: main
	avr-objcopy -O ihex -R .eeprom $< $@

.PHONY: upload clean
upload: main.hex
	avrdude -F -V -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUDS) -U flash:w:$<

clean:
	rm *.o *.hex main