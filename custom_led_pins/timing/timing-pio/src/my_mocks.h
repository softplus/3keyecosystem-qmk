#pragma once
#include <Arduino.h>
//#include <avr/io.h>

typedef struct {
    /* Perform any initialisation required for the other driver functions to work. */
    void (*init)(void);

    /* Set the brightness of a single LED in the buffer. */
    void (*set_value)(int index, uint8_t value);
    /* Set the brightness of all LEDS on the keyboard in the buffer. */
    void (*set_value_all)(uint8_t value);
    /* Flush any buffered changes to the hardware. */
    void (*flush)(void);
} led_matrix_driver_t;

// just mapping pins to Arduino digital pin numbers
#define B4 8
#define B5 9
#define B6 10
#define B7 11
#define C6 5
#define D7 6
#define F7 18

