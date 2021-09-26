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
#include QMK_KEYBOARD_H
#define TAPPING_TERM 200

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    LAYER_BASE, 
    LAYER_RACE
};

// Custom keycodes
enum {
  TD_00 = 0
};

// Tapdance types
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
} td_state_t;

/* Return an integer that corresponds to what kind of tap dance should be executed.
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
    } else if (state->count == 2) {
        if (!state->interrupted && !state->pressed) return TD_DOUBLE_TAP;
    }
    return TD_UNKNOWN; 
}

// Handle tap for button 0,0
void tap_00(qk_tap_dance_state_t *state, void *user_data) {
    td_state_t td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: 
            // next layer
            if (IS_LAYER_ON(LAYER_BASE)) 
                layer_move(LAYER_RACE);
            else layer_move(LAYER_BASE);
            //tap_code(KC_Z); 
            break; 
        case TD_DOUBLE_TAP: 
            SEND_STRING("Johannes\n");
            break; 
        default: break;
    }
}

// Tapdance references
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_00] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_00, NULL)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [LAYER_BASE] = LAYOUT_ortho_2x3(
        TD(TD_00),  KC_B,  KC_C,
        KC_D,  KC_E,  KC_F
    ),

    [LAYER_RACE] = LAYOUT_ortho_2x3(
        TD(TD_00), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT_ortho_2x3(
        TD(TD_00), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [3] = LAYOUT_ortho_2x3(
        TD(TD_00), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case LAYER_BASE:
            //rgblight_setrgb (0x00,  0x00, 0xFF);
            rgblight_mode(2);
            break;
        case LAYER_RACE:
            //rgblight_setrgb (0xFF,  0x00, 0x00);
            rgblight_mode(7);
            break;
        default: //  for any other layers, or the default layer
            //rgblight_setrgb (0x00,  0xFF, 0xFF);
            break;
    }
    return state;
}