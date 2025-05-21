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
#include "keycodes.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

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

enum layers {
    QWERTY,
    COLEMAK,
    EXT,
    SYM,
    NUM,
    FUN,
    GAMING,
};

/* enum custom_keycodes {}; */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_split_3x6_3(
        KC_NO, KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,   KC_Y,   KC_U,         KC_I,         KC_O,         KC_P,             KC_NO,
        KC_NO, LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,   KC_H,   RSFT_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), RGUI_T(KC_QUOTE), KC_NO,
        KC_NO, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,   KC_N,   KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,          KC_NO,
                                           KC_ESC,       KC_SPC,       KC_TAB, KC_ENT, KC_BSPC,      KC_TAB
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_BSPC: {
            static uint16_t registered_key = KC_NO;
            if (record->event.pressed) { // On key press.
                const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
                uint8_t shift_mods = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;
#else
                uint8_t shift_mods = mods & MOD_MASK_SHIFT;
#endif                            // NO_ACTION_ONESHOT
                if (shift_mods) { // At least one shift key is held.
                    registered_key = KC_DEL;
                    // If one shift is held, clear it from the mods. But if both
                    // shifts are held, leave as is to send Shift + Del.
                    if (shift_mods != MOD_MASK_SHIFT) {
#ifndef NO_ACTION_ONESHOT
                        del_oneshot_mods(MOD_MASK_SHIFT);
#endif // NO_ACTION_ONESHOT
                        unregister_mods(MOD_MASK_SHIFT);
                    }
                } else {
                    registered_key = KC_BSPC;
                }

                register_code(registered_key);
                set_mods(mods);
            } else { // On key release.
                unregister_code(registered_key);
            }
        }
            return false;

            // Other macros...
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

