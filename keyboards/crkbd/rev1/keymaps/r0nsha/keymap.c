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
#include "action_layer.h"
#include "color.h"
#include "keycodes.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

// TODO: layer: colemak
// TODO: layer: ext
// TODO: layer: sym
// TODO: layer: num
// TODO: layer: fun
// TODO: Move QK_BOOT, QK_RBT and EE_CLR to fun layer
// TODO: layer: gaming
// TODO: precondition
// TODO: lang switch button using custom functionality
// TODO: rgb lights per layer
// TODO: discord: show off!
// TODO: discord: ask about case

enum layers {
    QWERTY,
    COLEMAK,
    /* EXT, */
    /* SYM, */
    /* NUM, */
    /* FUN, */
    GAMING,
};

/* enum custom_keycodes {}; */

enum tap_dances {
    TD_GAMING,
    TD_COLEMAK,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_COLEMAK] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_NO, COLEMAK),
    [TD_GAMING]  = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_NO, GAMING),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_split_3x6_3(
        QK_BOOT,        KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,   KC_Y,   KC_U,         KC_I,         KC_O,         KC_P,             QK_BOOT,
        EE_CLR,         LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,   KC_H,   RSFT_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), RGUI_T(KC_QUOTE), RM_NEXT,
        TD(TD_COLEMAK), KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,   KC_N,   KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,          TD(TD_GAMING),
                                                    KC_ESC,       KC_SPC,       KC_TAB, KC_ENT, KC_BSPC,      KC_TAB
    ),

    [COLEMAK] = LAYOUT_split_3x6_3(
        _______, KC_Q, KC_W, KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT, _______,
        _______, KC_A, KC_R, KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    _______,
        _______, KC_Z, KC_X, KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, _______,
                             _______, _______, _______, _______, _______, _______
    ),

    [GAMING] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,    KC_Y,   KC_U,         KC_I,         KC_O,         KC_P,             _______,
        KC_LCTL, LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,    KC_H,   RSFT_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), RGUI_T(KC_QUOTE), _______,
        KC_LSFT, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,    KC_N,   KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,          _______,
                                             KC_ESC,       KC_SPC,       KC_LALT, KC_ENT, KC_BSPC,      KC_TAB
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

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
}

layer_state_t default_layer_set_user(layer_state_t state) {
    return layer_state_set_user(state);
}

static const hsv_t layer_colors[] = {
    [QWERTY]  = {HSV_ORANGE},
    [COLEMAK] = {HSV_MAGENTA},
    [GAMING]  = {HSV_RED},
};

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    hsv_t hsv = layer_colors[QWERTY];
    if (layer < sizeof(layer_colors) / sizeof(layer_colors[0])) {
        hsv = layer_colors[layer];
    }

    rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);
    return state;
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

