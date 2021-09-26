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

#include "quantum.h" 
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _ALTMODE
};


// Tap dance enums
enum {
    X_FIRST, X_THIRD
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMK_KEY1 = SAFE_RANGE,
    QMK_KEY2
}; 

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;
void x_finished_1(qk_tap_dance_state_t *state, void *user_data);
void x_finished_3(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        TD(X_FIRST), KC_MEDIA_PLAY_PAUSE, TD(X_THIRD) 
    ),
    [_ALTMODE] = LAYOUT(
        KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK
    )
};

const rgblight_segment_t PROGMEM _yes_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_GREEN} );
const rgblight_segment_t PROGMEM _no_layer[] = RGBLIGHT_LAYER_SEGMENTS( {1, 1, HSV_RED} );
const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST( _yes_layer, _no_layer );

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // for all keys
    //rgblight_blink_layer(0, 500);
    rgblight_blink_layer_repeat(0, 100, 4);

}

// RGB Modes
// 1 = Static
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient

void dip_switch_update_mask_user(uint32_t state) { 
    if (state) {
        //("#state0\n");
        layer_move(_BASE);
        rgblight_mode(2); // breathing
        rgblight_set_speed(50);
    } else {
        //("#state1\n");
        layer_move(_ALTMODE);
        rgblight_mode(7); // rainbow
        rgblight_set_speed(10);
    }
}

void matrix_init_user(void) { // Runs boot tasks for keyboard
	rgblight_enable();
	rgblight_sethsv(0,255,255);
	rgblight_mode(3);
    rgblight_set_speed(20);
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished_1(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: 
            tap_code(KC_MEDIA_PREV_TRACK); 
            break; 
        case TD_DOUBLE_TAP: 
            SEND_STRING("Johannes\n");
            break; 
        default: 
            break;
    }
}

void x_finished_3(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: 
            tap_code(KC_MEDIA_NEXT_TRACK); 
            break; 
        case TD_DOUBLE_TAP: 
            tap_code(KC_MEDIA_PREV_TRACK); 
            break; 
        default: 
            break;
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [X_FIRST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset), 
    [X_THIRD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_3, x_reset), 
};

