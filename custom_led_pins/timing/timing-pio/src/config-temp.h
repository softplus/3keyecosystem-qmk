#pragma once
#include "my_mocks.h"

#define LED_DRIVER_LED_COUNT 6
#define DRIVER_LED_TOTAL LED_DRIVER_LED_COUNT
//#define LED_MATRIX_PINS { F7, C6, B6, B5, B4, D7 }
#define LED_MATRIX_PINS { F7, C6, B6, B7, B4, D7 }

    typedef uint8_t pin_t;

#define MATRIX_ROWS 2
#define MATRIX_COLS 3
#define USE_CIE1931_CURVE
#define LED_MATRIX_TIME_DIVISOR 4
