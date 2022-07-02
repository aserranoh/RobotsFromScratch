
joystick: joystick.o mongoose.o
	gcc -o $@ $^ -static

mongoose.o: mongoose.c mongoose.h
	gcc -c $<

joystick.o: joystick.c
	gcc -c $<
