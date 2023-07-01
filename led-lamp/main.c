/*
lamp.c - Perform light effects with LEDS for a lamp.

This file is part of RobotsFromScratch.

Copyright 2023 Antonio Serrano Hernandez

RobotsFromScratch is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RobotsFromScratch is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RobotsFromScratch; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.
*/

#include <rfsavr/io.h>
#include <rfsavr/leds.h>
#include <rfsavr/timers.h>
#include "config.h"

////////////////////////////// Constants //////////////////////////////////

const uint8_t leds_step_delay_milliseconds = 100;
const struct rfs_grb_t colors[] = {{0, 1, 0}, {1, 0, 0}, {0, 0, 1}, {1, 1, 0}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
const uint8_t colors_size = 7;
const uint8_t intensities[] = {31, 63, 95, 127, 159, 191, 223, 255, 0};
const uint8_t intensities_size = 9;
const uint16_t long_press_duration_cycles = 10;     // 10 cycles = 1 second
const uint16_t intensity_mode_timeout_cycles = 20;  // 20 cycles = 2 seconds
const uint16_t cycle_time_ticks = 1562;             // 100 ms

/////////////////////////// Global variables //////////////////////////////

struct rfs_pin_t button_pin = {&BUTTON_PORT, BUTTON_PIN};
struct rfs_pin_t led_pin = {&LED_PORT, LED_PIN};
uint8_t button_state = 0;
uint8_t previous_button_state = 1;
struct rfs_grb_t led_values[LED_COUNT];
struct rfs_grb_t led_color;
uint8_t led_color_index = 0;
uint8_t led_intensity;
uint8_t led_intensity_index = 2;

enum rainbow_state_t {
    RED,
    MAGENTA,
    BLUE,
    CYAN,
    GREEN,
    YELLOW
} rainbow_state;

enum mode_t {
    COLOR_MODE,
    INTENSITY_MODE
} current_mode = COLOR_MODE;

struct rfs_pin_t led_mode_pin = {&MODE_PORT, MODE_PIN};
struct rfs_timer_t timer;
uint8_t cycles = 0;

///////////////////////// Function declarations ///////////////////////////

void initialize();
void initialize_timer();
void compute_led_intensity();
void compute_index_color();
void read_inputs();
void process();
void do_button_pressed();
void do_button_released();
void do_button_short_click();
void do_button_click_color_mode();
void do_button_click_intensity_mode();
void do_button_long_click();
void do_button_not_pressed();
void process_color_mode();
void initialize_rainbow_color();
void compute_rainbow_color();
void set_led_colors();
void pause();
void write_outputs();

///////////////////////// Function definitions ///////////////////////////

/**
 * @brief Entry point of the program
 */
int main()
{
    initialize();
    while (1) {
        read_inputs();
        process();
        write_outputs();
    }
}

/**
 * @brief Initialize everything
 */
void initialize()
{
    rfs_pin_setinput_pullup(&button_pin);
    rfs_pin_setoutput(&led_pin);
    rfs_pin_setoutput(&led_mode_pin);
    initialize_timer();
    compute_led_intensity();
    compute_index_color();
}

/**
 * @brief Initialize the timer subsystem to use timestamps
 */
void initialize_timer()
{
    rfs_timer16_init(&timer, RFS_TIMER1);
    rfs_timer16_setmode(&timer, RFS_TIMER16_NORMAL);
    rfs_timer16_setclock(&timer, RFS_TIMER16_1024);
}

/**
 * @brief Compute the current LEDs intensity
 */
void compute_led_intensity()
{
    led_intensity = intensities[led_intensity_index];
}

/**
 * @brief Set the current color as the color from the list given the current index
 */
void compute_index_color()
{
    led_color = colors[led_color_index];

    led_color.green *= led_intensity;
    led_color.red *= led_intensity;
    led_color.blue *= led_intensity;
}

/**
 * @brief Read the inputs (in our case, the action button)
 */
void read_inputs()
{
    button_state = rfs_pin_read(&button_pin);
}

/**
 * @brief Process the inputs and compute outputs
 */
void process()
{
    if (!button_state && previous_button_state) {
        do_button_pressed();
    } else if (button_state && !previous_button_state) {
        do_button_released();
    } else if (button_state && previous_button_state) {
        do_button_not_pressed();
    }
    previous_button_state = button_state;

    process_color_mode();
}

/**
 * @brief The button has been pressed
 * 
 * Reset the counter to measure how much time we spend pressing the button
 */
void do_button_pressed()
{
    cycles = 0;
}

/**
 * @brief The button has been released
 */
void do_button_released()
{
    if (cycles < long_press_duration_cycles) {
        do_button_short_click();
    } else {
        do_button_long_click();
    }

    cycles = 0;
}

/**
 * @brief The button has been pressed for a short amount of time
 * 
 * Remain in the current mode and change the corresponding value
 */
void do_button_short_click()
{
    switch (current_mode) {
    case COLOR_MODE:
        do_button_click_color_mode();
        break;
    case INTENSITY_MODE:
        do_button_click_intensity_mode();
        break;
    }
}

/**
 * @brief The button has been clicked in color mode
 * 
 * Change the current color
 */
void do_button_click_color_mode()
{
    led_color_index++;
    if (led_color_index > colors_size) {
        led_color_index = 0;
    }

    if (led_color_index == colors_size) {
        initialize_rainbow_color();
    } else {
        compute_index_color();
    }
}

/**
 * @brief The button has been clicked in intensity mode
 * 
 * Change the current intensity
 */
void do_button_click_intensity_mode()
{
    led_intensity_index++;
    if (led_intensity_index >= intensities_size) {
        led_intensity_index = 0;
    }
    compute_led_intensity();
    if (led_color_index != colors_size) {
        compute_index_color();
    }
}

/**
 * @brief The button has been long pressed
 * 
 * Change from color mode to intensity mode
 */
void do_button_long_click()
{
    current_mode = INTENSITY_MODE;
    rfs_pin_set(&led_mode_pin);
}

/**
 * @brief The button is not being pressed
 * 
 * If in intensity mode, we have to go back to color mode if enough time has pased
 */
void do_button_not_pressed()
{
    if (current_mode == INTENSITY_MODE) {
        if (cycles > intensity_mode_timeout_cycles) {
            current_mode = COLOR_MODE;
            rfs_pin_reset(&led_mode_pin);
        }
    }
}

/**
 * @brief Make some processing when in color mode
 * 
 * If the current color is the rainbow one, we have to keep changing the color
 */
void process_color_mode()
{
    if (led_color_index == colors_size) {
        compute_rainbow_color();
    }
    set_led_colors();
    pause();
}

/**
 * @brief Initialize the rainbow color variables
 */
void initialize_rainbow_color()
{
    const struct rfs_grb_t initial_rainbow_color = {0, led_intensity, 0};
    led_color = initial_rainbow_color;
    rainbow_state = RED;
}

/**
 * @brief Compute a new color every cycle
 */
void compute_rainbow_color()
{
    switch (rainbow_state) {
    case RED:
        led_color.blue++;
        if (led_color.blue >= led_intensity) {
            rainbow_state++;
        }
        break;
    case MAGENTA:
        led_color.red--;
        if (led_color.red == 0) {
            rainbow_state++;
        }
        break;
    case BLUE:
        led_color.green++;
        if (led_color.green >= led_intensity) {
            rainbow_state++;
        }
        break;
    case CYAN:
        led_color.blue--;
        if (led_color.blue == 0) {
            rainbow_state++;
        }
        break;
    case GREEN:
        led_color.red++;
        if (led_color.red >= led_intensity) {
            rainbow_state++;
        }
        break;
    case YELLOW:
        led_color.green--;
        if (led_color.green == 0) {
            rainbow_state = RED;
        }
        break;
    }
}

/**
 * @brief Set the color of all the LEDs to the current led_color value
 */
void set_led_colors()
{
    for (int i = 0; i < LED_COUNT; i++) {
        led_values[i] = led_color;
    }
}

/**
 * @brief Slight pause at each processing cycle
 */
void pause()
{
    while (rfs_timer16_get(&timer) < cycle_time_ticks);
    rfs_timer16_set(&timer, 0);
    cycles++;
}

/**
 * @brief Write the outputs
 * 
 * In our case, write the computed LED values to the physical LED
 */
void write_outputs()
{
    rfs_leds_write(led_values, LED_COUNT, &led_pin);
}
