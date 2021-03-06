/*
Copyright 2021 John Mueller

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#define PRODUCT      4key1

#define MATRIX_ROW_PINS { F6, C6 }
#define MATRIX_COL_PINS { F4, D7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B7 // onboard LED

/* Defines for our LED matrix driver */
#ifdef LED_MATRIX_ENABLE
#define LED_DRIVER_COUNT 1
#define DRIVER_LED_TOTAL 4
#define LED_MATRIX_PINS { B2, D3, B5, D1 }
#define LED_MATRIX_KEYPRESSES
#define LED_MATRIX_FRAMEBUFFER_EFFECTS
#define LED_DISABLE_WHEN_USB_SUSPENDED true
#define LED_MATRIX_STARTUP_MODE LED_MATRIX_SOLID
#define DISABLE_LED_MATRIX_TYPING_HEATMAP
#define LED_MATRIX_MAXIMUM_BRIGHTNESS 255
//#define LED_MATRIX_LED_FLUSH_LIMIT 8 // default 16ms (calls 1/16ms)
#endif

#ifdef RGB_MATRIX_ENABLE
#define LED_DRIVER_COUNT 1
#define DRIVER_LED_TOTAL 4
#define LED_MATRIX_PINS { B2, D3, B5, D1 }
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
//#define RGB_MATRIX_LED_FLUSH_LIMIT 8 // default 16ms (calls 1/16ms)
#endif
