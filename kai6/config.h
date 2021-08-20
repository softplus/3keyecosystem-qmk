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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x1209
#define PRODUCT_ID   0x3308
#define DEVICE_VER   0x0001
#define MANUFACTURER 3-Key-Ecosystem
#define PRODUCT      kai6

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { F0, F1 }
#define MATRIX_COL_PINS { F4, F5, F6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Defines for our LED matrix driver */
//#define LED_MATRIX_ENABLE
#define LED_MATRIX_PINS { F7, C6, B6, B5, B4, D7 }
#define LED_DRIVER_LED_COUNT 6
#define DRIVER_LED_TOTAL LED_DRIVER_LED_COUNT
#define LED_MATRIX_KEYPRESSES
#define LED_MATRIX_FRAMEBUFFER_EFFECTS
#define LED_DISABLE_WHEN_USB_SUSPENDED true
#define LED_MATRIX_STARTUP_MODE LED_MATRIX_SOLID
#define DISABLE_LED_MATRIX_TYPING_HEATMAP
//#define LED_MATRIX_BINARY_CONTROL
#define LED_MATRIX_MAXIMUM_BRIGHTNESS 255
//#define LED_MATRIX_LED_FLUSH_LIMIT 8 // default 16ms (calls 1/16ms)
