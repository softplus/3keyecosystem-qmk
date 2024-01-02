/* Copyright 2021 John Mueller
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ledpins_as_matrix.h"

// For wait_us() -- via AVR libraries
#include <util/delay.h> 

// For CIE1931_CURVE mapping of brightness -> PWM values
#include "led_tables.h"

// individual LED brightness & pins used
uint8_t g_led_brightness[DRIVER_LED_TOTAL];
const pin_t g_led_pins[DRIVER_LED_TOTAL] = LED_MATRIX_PINS;

// if setting HIGH turns LED off
#ifdef LED_MATRIX_PIN_SINK
#    define led_pin_on(pin) writePinLow(pin)
#    define led_pin_off(pin) writePinHigh(pin)
#else
#    define led_pin_on(pin) writePinHigh(pin)
#    define led_pin_off(pin) writePinLow(pin)
#endif

void ledpins_init(void) {
    /* initialize all pins for output, turn them off */
    for (uint8_t x = 0; x < DRIVER_LED_TOTAL; x++) {
        setPinOutput(g_led_pins[x]);
        led_pin_off(g_led_pins[x]);
    }
}

void ledpins_flush(void) {
    /* Parallel bit-banged PWM implementation. 
     * Runtime is O(256us).
     * LEDs stay on if max brightness 
     */
    // get PWM times per LED & set initial pin output
    uint8_t pwm_time[DRIVER_LED_TOTAL];
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        pwm_time[i] = pgm_read_byte(&CIE1931_CURVE[g_led_brightness[i]]) / LED_MATRIX_PIN_PWM_TIME;
        #ifdef LED_MATRIX_PIN_BINARY_CONTROL
            if (pwm_time[i] > LED_MATRIX_PIN_BINARY_THRESHOLD) {
                led_pin_on(g_led_pins[i]);
            } else { 
                led_pin_off(g_led_pins[i]);
            }
        #else
            if (pwm_time[i] > 0) {
                led_pin_on(g_led_pins[i]);
            } else {
                led_pin_off(g_led_pins[i]);
            }
        #endif
    }
    // do PWM for all pins at once
    #ifndef LED_MATRIX_PIN_BINARY_CONTROL
        for (uint8_t t = 0; t < 256 / LED_MATRIX_PIN_PWM_TIME; t++) {
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (pwm_time[i]==t) led_pin_off(g_led_pins[i]);
            }
            wait_us(LED_MATRIX_PIN_PWM_TIME);
        }
    #endif
}

#ifdef LED_MATRIX_ENABLE
void ledpins_set_value(int index, uint8_t value) {
    /* Set the brighness for a single LED. */
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        g_led_brightness[index] = value;
    }
}

void ledpins_set_value_all(uint8_t value) {
    /* Set the brighness for all LEDs. */
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        ledpins_set_value(i, value);
    }
}
const led_matrix_driver_t led_matrix_driver = {
    /* functions for our LED matrix driver */
    .init  = ledpins_init,
    .flush = ledpins_flush,
    .set_value = ledpins_set_value,
    .set_value_all = ledpins_set_value_all
};
#endif

#ifdef RGB_MATRIX_ENABLE
void ledpins_set_color(int index, uint8_t value_r, uint8_t value_g, uint8_t value_b) {
    /* Set the brighness for a single LED. */
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        // value is average across colors
        g_led_brightness[index] = ( value_r + value_g + value_b ) /3;
    }
}

void ledpins_set_color_all(uint8_t value_r, uint8_t value_g, uint8_t value_b) {
    /* Set the brighness for all LEDs. */
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        ledpins_set_color(i, value_r, value_g, value_b);
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    /* functions for our LED matrix driver */
    .init  = ledpins_init,
    .flush = ledpins_flush,
    .set_color = ledpins_set_color,
    .set_color_all = ledpins_set_color_all
};
#endif
