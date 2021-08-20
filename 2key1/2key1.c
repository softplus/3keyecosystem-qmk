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
#include "2key1.h"

#ifdef LED_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key matrix to LED index
  {   0, 1 }
}, {
  // LED index to equidistant physical position
  {   0,   0 }, {  223,   0 } 
}, {
  // LED index to flag
  LED_FLAG_ALL, LED_FLAG_ALL
} };
#endif
