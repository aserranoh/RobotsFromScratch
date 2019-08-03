
MCU = atmega328p
F = 16000000UL
CFLAGS = -Os -Wall -std=c11

objects = usart.o

librfsavr.a: $(objects)
	ar rcs librfsavr.a $^

%.o: %.c
	avr-gcc $(CFLAGS) -DF_CPU=$(F) -mmcu=$(MCU) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o librfsavr.a

