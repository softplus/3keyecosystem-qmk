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
    LAYER_RACE, 
    LAYER_NEXT
};

// Custom keycodes
enum {
  TD_MODE,
  TD_NEXT,
  TX_1_01, TX_1_02, TX_1_03,
  TX_2_01, TX_2_02, TX_2_03
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

// Handle tap for mode-button
void tap_mode(qk_tap_dance_state_t *state, void *user_data) {
    td_state_t td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: 
            // next layer
            if (IS_LAYER_ON(LAYER_BASE)) 
                layer_move(LAYER_RACE);
            else if (IS_LAYER_ON(LAYER_RACE))
                layer_move(LAYER_NEXT);
            else layer_move(LAYER_BASE);
            break; 
        case TD_DOUBLE_TAP: 
            SEND_STRING("Johannes\n");
            break; 
        default: break;
    }
}

// Handle tap for next-button
void tap_next(qk_tap_dance_state_t *state, void *user_data) {
    td_state_t td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // media next
            tap_code(KC_MEDIA_NEXT_TRACK);
            //rgb_matrix_mode_noeeprom(1);
            break; 
        case TD_DOUBLE_TAP: 
            tap_code(KC_MEDIA_PLAY_PAUSE);
            //rgb_matrix_mode_noeeprom(3);
            break; 
        default: break;
    }
}

// Tapdance references
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_MODE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_mode, NULL), 
  [TD_NEXT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_next, NULL) 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [LAYER_BASE] = LAYOUT_ortho_2x3(
        TD(TD_NEXT),  TD(TD_NEXT),   RGB_TOG,
        TD(TD_MODE),  LALT(KC_TAB),  KC_F10
    ),

    [LAYER_RACE] = LAYOUT_ortho_2x3(
        KC_TRNS, TX_1_01, TX_1_03,
        KC_TRNS, TX_1_02, KC_TRNS
    ),

    [LAYER_NEXT] = LAYOUT_ortho_2x3(
        KC_TRNS, TX_2_01, TX_2_03,
        KC_TRNS, TX_2_02, KC_TRNS
    ),

    [3] = LAYOUT_ortho_2x3(
        KC_TRNS, KC_9, KC_7,
        KC_TRNS, KC_8, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    uint8_t clockbyte=0;
    clockbyte = TCNT0 % 256;

    const char *str_1[] = {
        "Is there a starbucks here?", "I need a coffee.", 
        "Where's the coffee?", "Garcon, une espresso.",
        "Coffee cup of Ride Ons!",
        "Take expresso pulls, leave ride ons!",
        "I wish they had a coffee bar here."

    };
    const char *str_2[] = {
        "Switzerland checking in", "Hi from switzerland", 
        "Land-of-cheese says hi",
        "Switzerland in the house."
    };
    const char *str_3[] = {
        "I didn't ask for a hill.", "Hills? Nooo.",
        "Someone remove the uphill."
    };
    const char *str_4[] = {
        "Be mindful of the traffic, Coco!",
        "Dance on those pedals like it's 1999, Brevy.",
        "Don't forget to breathe in, breathe out, wax on, wax off!",
        "I perspire to perspire!",
        "Rip snorter! Snort ripper!",
        "We're as fast as a roo of mobs!",
        "Speed is only temporary!",
        "If you're succeeding, you're tiring!",
        "Coco, I'll keep a steady pace for you to follow.",
        "No worries, Coco!",
        "Ride Ons for your weird yakka!",
        "Slide slide slide!",
        "Let's keep a brisk bludger, we're no Brevets..."
    };

    uint8_t selected;

    switch (keycode) {
        case TX_1_01:
            send_string("m ");
            selected = clockbyte % sizeof(str_1) / sizeof(str_1[0]);
            send_string(str_1[selected]);
            return false;

        case TX_1_02:
            selected = clockbyte % sizeof(str_2) / sizeof(str_2[0]);
            send_string(str_2[selected]);
            return false;            

        case TX_1_03:
            send_string("m ");
            selected = clockbyte % sizeof(str_3) / sizeof(str_3[0]);
            send_string(str_3[selected]);
            return false;            

        case TX_2_01:
        case TX_2_02:
        case TX_2_03:
            send_string("m ");
            selected = clockbyte % sizeof(str_4) / sizeof(str_4[0]);
            send_string(str_4[selected]);
            return false;            
    }
    return true; // all other codes
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // colors from https://github.com/qmk/qmk_firmware/blob/master/quantum/color.h
    switch (get_highest_layer(state)) {
        case LAYER_BASE:
            // HSV_PINK w/reduced val
            rgb_matrix_sethsv(234, 128, 64); // original: 200, 20, 64
            rgblight_mode(RGB_MATRIX_ALPHAS_MODS); // 2
            break;
        case LAYER_RACE:
            // HSV_GOLD w/reduced Val
            rgb_matrix_sethsv(36, 255, 128);
            rgblight_mode(RGB_MATRIX_BAND_VAL); // 7
            break;
        case LAYER_NEXT:
            // HSV_SPRINGGREEN w/reduced val
            rgb_matrix_sethsv(106, 255, 128);
            rgblight_mode(RGB_MATRIX_BAND_VAL); // 7
            break;
        default: //  for any other layers, or the default layer
            rgb_matrix_sethsv(HSV_WHITE);
            break;
    } /* */
    return state;
}