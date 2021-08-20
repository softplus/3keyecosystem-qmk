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
#include "custom_led_pins.h"

// ideas for direct pin LED code are from
// https://git.bureau-wehrmann.eu/dwehrmann/qmk_firmware/-/commit/f8896d8b92abbd28c87797f9b75f87c895bd8bea

// for wait_us() -- via AVR libraries
#include <util/delay.h> 
void wait_us(int mikroSec)
{
  //_delay_loop_2( 1*(F_CPU/(1000000/4)) * mikroSec);  
  // 4 Zyklen warteschleife
}

// for CIE1931_CURVE mapping of brightness -> PWM values
#include "led_tables.h"

// individual LED brightness & pins used
uint8_t g_led_brightness[LED_DRIVER_LED_COUNT];
const pin_t g_led_pins[LED_DRIVER_LED_COUNT] = LED_MATRIX_PINS;

#define led_pin_on(pin) digitalWrite(pin, HIGH);
#define led_pin_off(pin) digitalWrite(pin, LOW);

void ledpins_init(void) {
    /* initialize all pins for output, set them off */
    for (uint8_t x = 0; x < LED_DRIVER_LED_COUNT; x++) {
        //setPinOutput(g_led_pins[x]);
        pinMode(g_led_pins[x], OUTPUT);
        led_pin_off(g_led_pins[x]);
    }
}

void ledpins_flush(void) {
    /* Parallel bit-banged PWM implementation. Runtime generally <1ms.
     * LEDs stay on if max brightness */
    Serial.println("y"); 
    int pwm_time[LED_DRIVER_LED_COUNT];
    const uint8_t time_divisor = 4;//LED_MATRIX_TIME_DIVISOR;
    // get PWM timings & set initial pin output
    for (uint8_t i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        //pwm_time[i] = pgm_read_byte(&CIE1931_CURVE[g_led_brightness[i]]) / time_divisor;
        pwm_time[i] =  (g_led_brightness[i] / time_divisor);
        Serial.print(".. "); Serial.print(i); Serial.print(":" );
        Serial.print(g_led_pins[i]); Serial.print("=");
        Serial.print(pwm_time[i]);
        if (pwm_time[i] > 0) {
            //Serial.print("on"); 
            //led_pin_on(g_led_pins[i]);
        } else {
            //Serial.print("off"); 
            //led_pin_off(g_led_pins[i]);
        }
    }
    Serial.println("z"); return;
    // do PWM for all pins at once
    for (uint8_t t = 0; t < 256 / time_divisor; t++) {
        for (uint8_t i = 0; i < LED_DRIVER_LED_COUNT; i++) {
            if (pwm_time[i]==t) led_pin_off(g_led_pins[i]);
        }
        wait_us(LED_MATRIX_WAIT_US_PWM);
    }
}

void ledpins_set_value(int index, uint8_t value) {
    /* Set the brighness for a single LED. */
    if (index >= 0 && index < LED_DRIVER_LED_COUNT) {
        g_led_brightness[index] = value;
    }
}

void ledpins_set_value_all(uint8_t value) {
    /* Set the brighness for all LEDs. */
    for (int i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        ledpins_set_value(i, value);
    }
}
/*
const led_matrix_driver_t led_matrix_driver = {
    //functions for our LED matrix driver 
    .init  = ledpins_init,
    .flush = ledpins_flush,
    .set_value = ledpins_set_value,
    .set_value_all = ledpins_set_value_all,
};
*/