/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include <stdint.h>
#include <stdbool.h>
#include QMK_KEYBOARD_H

enum layers {
    QWERTY,
    COLEMAK,
    EXT,
    SYM,
    NUM,
    FUN,
    GAMING,
};

enum custom_keycodes {
    BSPC_DEL = SAFE_RANGE,
};

// TODO: home row mods
// TODO: base: blue
// TODO: layer: colemak
// TODO: layer: ext
// TODO: layer: sym
// TODO: layer: num
// TODO: layer: fun
// TODO: layer: gaming
// TODO: precondition
// TODO: lang switch button using custom functionality
// TODO: discord: show off!
// TODO: discord: ask about case

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_split_3x6_3(
        KC_NO, KC_Q,         KC_W, KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,     KC_I,    KC_O,   KC_P,     KC_NO,
        KC_NO, LGUI_T(KC_A), KC_S, KC_D,   KC_F,   KC_G,   KC_H,   KC_J,     KC_K,    KC_L,   KC_QUOTE, KC_NO,
        KC_NO, KC_Z,         KC_X, KC_C,   KC_V,   KC_B,   KC_N,   KC_M,     KC_COMM, KC_DOT, KC_SLSH,  KC_NO,
                                   KC_ESC, KC_SPC, KC_TAB, KC_ENT, BSPC_DEL, KC_TAB
    ),
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    static uint8_t saved_mods = 0;

    switch (keycode) {
        case BSPC_DEL:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;

                if (saved_mods == MOD_MASK_SHIFT) { // Both shifts pressed
                    register_code(KC_DEL);
                } else if (saved_mods) {  // One shift pressed
                    del_mods(saved_mods); // Remove any Shifts present
                    register_code(KC_DEL);
                    add_mods(saved_mods); // Add shifts again
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
            }
            return false;
        default:
            break;
    }

    return true;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [1] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [2] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [3] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
};
#endif

