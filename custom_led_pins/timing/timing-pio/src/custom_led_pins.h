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

#include "my_mocks.h"
#include "config-temp.h"

const led_matrix_driver_t led_matrix_driver;

#define LED_MATRIX_WAIT_US_PWM 4 // default 1us
#define LED_MATRIX_TIME_DIVISOR 4 // makes loop shorter

void ledpins_init(void);
void ledpins_flush(void);
void ledpins_set_value(int index, uint8_t value);
void ledpins_set_value_all(uint8_t value);