# LED lamp controller

## Introduction

This code, which runs in a AVR microcontroller, implements the driver of an LED lamp. Concretely, it controls an LED strip consisting of a given number of RGB LEDs.

## Features

The driver has the following features:

### WS2812B protocol

It controls an RGB LED strip using the WS2812B serial line protocol.

### Control button

It uses a button to control the light effects. The button has two functions:

* To set the mode of the lamp: the lamp can be in two modes: color mode and intensity mode.
* To change the current values of color/intensity: in color mode, the button allows to change the color of the lamp. In intensity mode, the button allows to change the intensity of the colors.

By default, the lamp is in color mode. In color mode, clicking the button (for less than a second) allows to change the color of the light (it circles through the following colors: red, green, blue, yellow, magenta, cyan, white and rainbow). The rainbow color is simply that the colors keep changing automatically.

When the button is pressed for more than one second, the lamp goes to intensity mode. The lamp will fall back to color mode if there's no action with the button within 2 seconds.

In intensity mode, the intensity of the light can be changed. By default, the intensity is set to 3. There's 9 levels of intensity. Intensity 0 means that the lamp is totally off. Intensity 8 is the maximum intensity.

The driver uses the internal pull-up resistor to drive the button. So, one pin of the button should be connected to the microcontroller input and the other pin directly to ground.

### Mode LED

It can also be a mode LED connected. If used, this LED will be ON if the driver is in intensity mode, and OFF otherwise.

## Dependencies

To compile and upload this code, you will need the following things:

* AVR toolchain: notably, the packages `avr-gcc`, `avr-libc` and `avrdude`.
* The `librfsavr` library. This is a library that contains some routines that abstract the low level management of the AVR microcontrollers. You can download this library from here: https://github.com/aserranoh/librfsavr.

## Compiling the code

Before compiling the code, you can edit the file `config.h` in order to set the right values of your hardware implementation. This are the definitions that can be changed:

* **LED_COUNT**: Number of LEDs in the strip or ring (default is `12`).
* **BUTTON_PORT**: Port where the button is connected (default is `PORTD`).
* **BUTTON_PIN**: Pin in BUTTON_PORT where the button is connected (default is `2`).
* **LED_PORT**: Port where the LED strip is connected (default is `PORTB`).
* **LED_PIN**: Pin in LED_PORT where the LED strip is connected (default is `3`).
* **MODE_PORT**: Port where the the mode LED is connected (default is `PORTB`). The mode LED is just an LED that turns on when the driver is in intensity mode, and remains off in color mode.
* **MODE_PIN**: Pin in MODE_PORT where the button is connected (default is `5`). The default combination of MODE_PORT/MODE_PIN corresponts to the builtin LED in the Arduino Nano board.

To compile the controller, use the following command:

```console
make
```

Then, to upload the code to the AVR microcontroller (using `avrdude`), execute:

```console
make upload
```

The `make` command accepts some arguments:

* **MCU**: The target AVR microcontroller (default is the famous `atmega328p`).
* **F**: The microcontroller's frequency (default is `16MHz`).

The `make upload` command accepts the following arguments:

* **MCU**: The target AVR microcontroller (default is the famous `atmega328p`).
* **PORT**: Devide where the microcontroller is connected, in order to upload the code (default is `/dev/ttyUSB0`).
* **BAUDS**: Communication speed for upload (default is `57600`).
* **PROGRAMMER**: Programmer to use with avrdude (default is `arduino`).

The default values are adequate for an LED ring of 12 LEDs, and to use this driver with the **Arduino Nano**.

For instante, if you want to compile the code for an Arduino UNO the following commands can be used:

```console
make
make PORT=/dev/ttyACM0 BAUDS=115200 upload
```

Enjoy!