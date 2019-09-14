
MCU = atmega328p
F = 16000000UL
CFLAGS = -O2 -Wall -std=c11
LIBRFSAVR_PATH = ../../../librfsavr/src

ultrasonic1.hex: ultrasonic1
	avr-objcopy -O ihex -R .eeprom $< $@

ultrasonic1: ultrasonic1.o librfsavr
	avr-gcc -mmcu=$(MCU) $< -o $@ -L$(LIBRFSAVR_PATH) -lrfsavr

%.o: %.c
	avr-gcc $(CFLAGS) -DF_CPU=$(F) -mmcu=$(MCU) -c -o $@ $< -I $(LIBRFSAVR_PATH)

.PHONY: clean librfsavr

librfsavr:
	make -C $(LIBRFSAVR_PATH)

clean:
	rm *.o ultrasonic1

