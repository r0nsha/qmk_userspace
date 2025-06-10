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

#include <stdbool.h>
#include <stdint.h>

#include "action.h"
#include "action_layer.h"
#include "caps_word.h"
#include "color.h"
#include "keyboard.h"
#include "keycode_string.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

enum layers {
    QWERTY,
    COLEMAK,
    GAMING,
    EXT,
    SYM,
    NUM,
    FUN,
};

static const hsv_t layer_colors[] = {
    [QWERTY] = {HSV_SPRINGGREEN}, [COLEMAK] = {HSV_MAGENTA}, [GAMING] = {HSV_RED}, [EXT] = {HSV_PINK}, [SYM] = {HSV_ORANGE}, [NUM] = {HSV_BLUE}, [FUN] = {HSV_PURPLE},
};

static const char* layer_names[] = {
    [QWERTY] = "QWERTY", [COLEMAK] = "COLEMAK", [GAMING] = "GAMING", [EXT] = "EXT", [SYM] = "SYM", [NUM] = "NUM", [FUN] = "FUN",
};

enum custom_keycodes {
    KC_LANG = SAFE_RANGE,
};

KEYCODE_STRING_NAMES_USER(KEYCODE_STRING_NAME(KC_LANG));

enum tap_dances {
    TD_GAMING,
    TD_COLEMAK,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_COLEMAK] = ACTION_TAP_DANCE_LAYER_TOGGLE(XXXXXXX, COLEMAK),
    [TD_GAMING]  = ACTION_TAP_DANCE_LAYER_TOGGLE(XXXXXXX, GAMING),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_split_3x6_3(
        XXXXXXX,        KC_Q,         KC_W,         KC_E,            KC_R,            KC_T,   KC_Y,   KC_U,             KC_I,         KC_O,         KC_P,             XXXXXXX,
        XXXXXXX,        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D),    LSFT_T(KC_F),    KC_G,   KC_H,   RSFT_T(KC_J),     RCTL_T(KC_K), LALT_T(KC_L), RGUI_T(KC_QUOTE), XXXXXXX,
        TD(TD_COLEMAK), KC_Z,         KC_X,         KC_C,            KC_V,            KC_B,   KC_N,   KC_M,             KC_COMM,      KC_DOT,       KC_SLSH,          TD(TD_GAMING),
                                                    LT(NUM, KC_ESC), LT(EXT, KC_SPC), KC_TAB, KC_ENT, LT(SYM, KC_BSPC), MO(FUN)
    ),

    [COLEMAK] = LAYOUT_split_3x6_3(
        _______, KC_Q, KC_W, KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT, _______,
        _______, KC_A, KC_R, KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    _______,
        _______, KC_Z, KC_X, KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, _______,
                             _______, _______, _______, _______, _______, _______
    ),

    [GAMING] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E,            KC_R,   KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,     _______,
        KC_LCTL, KC_A, KC_S, KC_D,            KC_F,   KC_G,    KC_H,   KC_J,    KC_K,    KC_L,   KC_QUOTE, _______,
        KC_LSFT, KC_Z, KC_X, KC_C,            KC_V,   KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,  _______,
                             LT(NUM, KC_ESC), KC_SPC, KC_LALT, KC_ENT, KC_BSPC, MO(FUN)
    ),

    [EXT] = LAYOUT_split_3x6_3(
        _______, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_ESC, _______,
        _______, LGUI(XXXXXXX), LALT(XXXXXXX), LCTL(XXXXXXX), LSFT(XXXXXXX), XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT, _______,
        _______, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, KC_LANG, CW_TOGG, KC_DEL,  KC_INS,  KC_TAB, _______,
                                               _______,       _______,       _______, _______, _______, _______
    ),

    [SYM] = LAYOUT_split_3x6_3(
        _______, KC_AT,   KC_LABK, KC_RABK, KC_PERC, KC_BSLS, KC_CIRC, KC_AMPR, KC_LBRC, KC_RBRC, KC_HASH, _______,
        _______, KC_EXLM, KC_MINS, KC_SLSH, KC_EQL,  KC_PIPE, KC_SCLN, KC_COLN, KC_LPRN, KC_RPRN, KC_DQUO, _______,
        _______, KC_TILD, KC_PLUS, KC_ASTR, KC_UNDS, KC_BSLS, KC_GRV,  KC_DLR,  KC_LCBR, KC_RCBR, KC_QUES, _______,
                                   _______, _______, _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_split_3x6_3(
        _______, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, KC_ASTR, KC_7, KC_8, KC_9, KC_PLUS, _______,
        _______, LGUI(XXXXXXX), LALT(XXXXXXX), LCTL(XXXXXXX), LSFT(XXXXXXX), KC_EQL,  KC_SLSH, KC_4, KC_5, KC_6, KC_MINS, _______,
        _______, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX, KC_1, KC_2, KC_3, KC_DOT,  _______,
                                               _______,       _______,       _______, _______, KC_0, KC_0
    ),

    [FUN] = LAYOUT_split_3x6_3(
        RM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,  KC_F7,  KC_F8, KC_F9, QK_BOOT,
        RM_NEXT, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRIU, XXXXXXX, KC_F11,  KC_F4,  KC_F5, KC_F6, QK_RBT,
        RM_PREV, KC_PSCR, KC_VOLD, KC_MUTE, KC_VOLU, KC_BRID, XXXXXXX, KC_F10,  KC_F1,  KC_F2, KC_F3, EE_CLR,
                                   _______, _______, _______, _______, _______, _______
    ),
};

static const char* last_key_str = "None";
bool               is_qwerty    = true;

bool               process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        last_key_str = get_keycode_string(keycode);
    }

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

            return false;
        }
        case KC_LANG: {
            if (record->event.pressed) {
                tap_code16(LGUI(KC_SPACE));

                // TODO: uncomment when stop being a pussy and officially move to colemak
                /* if (is_qwerty) { */
                /*     layer_move(COLEMAK); */
                /* } else { */
                /*     layer_move(QWERTY); */
                /* } */

                /* is_qwerty = !is_qwerty; */
            }

            return false;
        }
    }

    return true;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
    hsv_t default_layer_color = layer_colors[QWERTY];
    rgb_matrix_sethsv(default_layer_color.h, default_layer_color.s, default_layer_color.v);
}

layer_state_t default_layer_set_user(layer_state_t state) {
    return layer_state_set_user(state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    hsv_t   hsv   = layer_colors[QWERTY];
    if (layer < sizeof(layer_colors) / sizeof(layer_colors[0])) {
        hsv = layer_colors[layer];
    }

    rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);
    return state;
}

#ifdef OLED_ENABLE
void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}

void oled_render_layer(void) {
    uint8_t layer = get_highest_layer(layer_state);

    oled_write_P(PSTR("Layer: "), false);

    const char* layer_name = "Unknown";
    if (layer < sizeof(layer_names) / sizeof(layer_names[0])) {
        layer_name = layer_names[layer];
    }

    oled_write_ln_P(PSTR(layer_name), false);
}

void oled_render_key(void) {
    oled_write_P(PSTR("Key: "), false);
    oled_write_ln_P(PSTR(last_key_str), false);
}

void oled_render_mods(void) {
    uint8_t mods = get_mods();
    oled_write(is_caps_word_on() ? "CAPW " : "      ", false);
    oled_write((mods & MOD_MASK_SHIFT) ? "SHIFT " : "      ", false);
    oled_write((mods & MOD_MASK_CTRL) ? "CTRL " : "     ", false);
    oled_write((mods & MOD_MASK_ALT) ? "ALT " : "    ", false);
    oled_write((mods & MOD_MASK_GUI) ? "GUI" : "   ", false);
    oled_write("\n", false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer();
        oled_render_key();
        oled_render_mods();
    } else {
        oled_render_logo();
    }

    return false;
}
#endif

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

