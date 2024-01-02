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
#pragma once

#include "quantum.h"

/*
 * Makes individually connected LEDs act like either a LED or RGB matrix for QMK.
 * LEDs are controlled with PWM, or optonally with a fixed threshold.
 * Why? Because I made boards with individual LEDs and RGB matrixes, and
 * want to use a single shared configuration.
 * 
 * Set in rules.mk:
 * # for RGB Matrix:
 * RGB_MATRIX_ENABLE = yes		# Enable RGB matrix
 * RGB_MATRIX_DRIVER = custom	# Select WS2812 driver for RGB matrix
 * 
 * # for LED Matrix:
 * LED_MATRIX_ENABLE = yes		# Enable LED matrix
 * LED_MATRIX_DRIVER = custom	# Select WS2812 driver for LED matrix
 * 
 * # for both
 * SRC += ../common/ledpins_as_matrix.c	# ... and add our custom driver code
 * 
 * Required settings in common.h or [keyboard].h
 * #define LED_DRIVER_COUNT 1 // how many LED drivers there are (should be 1)
 * #define DRIVER_LED_TOTAL 6 // how many LEDs there are
 * #define LED_MATRIX_PINS { F7, C6, B6, B5, B4, D7 } // the pins used
 * 
 * Required in [keyboard].c
 * led_config_t g_led_config = { ... } // definition
 * 
 * Optional settings in common.h or [keyboard].h
 * #define LED_MATRIX_PIN_SINK // if the LEDs are set LOW to turn on
 * #define LED_MATRIX_PIN_BINARY_CONTROL // if LEDS should either be on or off, not PWM controlled
 * #define LED_MATRIX_PIN_BINARY_THRESHOLD 32 // binary threshold, if enabled
 * #define LED_MATRIX_PIN_PWM_TIME 4 // [us] time-slice for PWM (default: 4)
 * 
 * To control brightness (less = brighter, but makes keyboard slower):
 * #define LED_MATRIX_LED_FLUSH_LIMIT 8 // how often PWM is called [ms], default: 16, for LED Matrix
 * #define RGB_MATRIX_LED_FLUSH_LIMIT 8 // how often PWM is called [ms], default: 16, for RGB Matrix
 * 
 * + the preferred LED_MATRIX_* or RGB_MATRIX_* settings
 */

// define structures (and fail here if neither LED nor RGB matrix are enbled)
#ifdef LED_MATRIX_ENABLE
const led_matrix_driver_t led_matrix_driver;
#endif
#ifdef RGB_MATRIX_ENABLE
const rgb_matrix_driver_t rgb_matrix_driver;
#endif

// defaults
#ifndef LED_MATRIX_PIN_PWM_TIME
#define LED_MATRIX_PIN_PWM_TIME 4
#endif

#ifndef LED_MATRIX_PIN_BINARY_THRESHOLD
#define LED_MATRIX_PIN_BINARY_THRESHOLD 32
#endif
