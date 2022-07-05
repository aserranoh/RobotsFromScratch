
joystick: joystick.o mongoose.o utils.o
	gcc -o $@ $^ -static

mongoose.o: mongoose.c mongoose.h
	gcc -c -O2 $<

joystick.o: joystick.c
	gcc -c -O2 $<

utils.o: utils.c utils.h
	gcc -c -O2 $<
