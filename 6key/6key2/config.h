/*
Copyright 2021 johnmu

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

#define MATRIX_ROW_PINS { F6, C6 }
#define MATRIX_COL_PINS { F4, B5, D7 } // rev1: F4,D7,D3 ; rev2: F4,B5,D7

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B7 // onboard LED

#ifdef RGB_MATRIX_ENABLE
#define WS2812_DI_PIN B2
#define DRIVER_LED_TOTAL 6
#define RGB_MATRIX_STARTUP_HUE 200
#define RGB_MATRIX_STARTUP_SPD 20
#define RGB_MATRIX_STARTUP_VAL 128
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
// must ENABLE any used RGB_MATRIX effects in {keymap}/config.h
// see https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
// and https://www.reddit.com/r/olkb/comments/r3r693/qmk_breaking_changes_2021_november_27_changelog/
#endif
