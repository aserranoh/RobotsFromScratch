
MCU = atmega328p
F = 16000000UL
CFLAGS = -O2 -Wall -std=c11

objects = core.o interrupt.o pin.o timer.o ultrasonic.o usart.o

librfsavr.a: $(objects)
	ar rcs librfsavr.a $^

%.o: %.c
	avr-gcc $(CFLAGS) -DF_CPU=$(F) -mmcu=$(MCU) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o librfsavr.a

