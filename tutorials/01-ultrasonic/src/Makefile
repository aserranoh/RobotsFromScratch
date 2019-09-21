
MCU = atmega328p
F = 16000000UL
CFLAGS = -O2 -Wall -std=c11
LIBRFSAVR_PATH = ../../../librfsavr/src
BAUDS = 115200

ultrasonic1.hex: ultrasonic1
	avr-objcopy -O ihex -R .eeprom $< $@

ultrasonic1: ultrasonic1.o librfsavr
	avr-gcc -mmcu=$(MCU) $< -o $@ -L$(LIBRFSAVR_PATH) -lrfsavr

%.o: %.c
	avr-gcc $(CFLAGS) -DF_CPU=$(F) -mmcu=$(MCU) -c -o $@ $< -I $(LIBRFSAVR_PATH)

.PHONY: clean librfsavr upload

librfsavr:
	make -C $(LIBRFSAVR_PATH)

upload: ultrasonic1.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P $(PORT) -b $(BAUDS) -U flash:w:$<

clean:
	rm *.o ultrasonic1 *.hex

