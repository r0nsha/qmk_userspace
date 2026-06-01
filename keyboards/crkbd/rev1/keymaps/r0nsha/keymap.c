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

#include "keycodes.h"
#include "quantum_keycodes.h"
#include "users/holykeebs/holykeebs.h"

enum layers {
    QWERTY,
    COLEMAK,
    GAMING,
    EXT,
    SYM,
    NUM,
    FUN,
#ifdef POINTING_DEVICE_ENABLE
    MOUSE,
#endif
};

static const hsv_t layer_colors[] = {
    [QWERTY] = {HSV_ORANGE},    [COLEMAK] = {HSV_MAGENTA}, [GAMING] = {HSV_RED},
    [EXT] = {HSV_CYAN},         [SYM] = {HSV_SPRINGGREEN}, [NUM] = {HSV_BLUE},
    [FUN] = {HSV_PURPLE},
#ifdef POINTING_DEVICE_ENABLE
    [MOUSE] = {HSV_CHARTREUSE},
#endif
};

#ifdef POINTING_DEVICE_ENABLE
#define TAB_KEY LT(MOUSE, KC_TAB)
#else
#define TAB_KEY KC_TAB
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_split_3x6_3(
        XXXXXXX,     KC_Q,        KC_W,        KC_E,            KC_R,            KC_T,    KC_Y,   KC_U,        KC_I,        KC_O,        KC_P,           XXXXXXX,
        XXXXXXX,     GUI_T(KC_A), ALT_T(KC_S), CTL_T(KC_D),     SFT_T(KC_F),     KC_G,    KC_H,   SFT_T(KC_J), CTL_T(KC_K), ALT_T(KC_L), GUI_T(KC_QUOT), XXXXXXX,
        TT(COLEMAK), KC_Z,        KC_X,        KC_C,            KC_V,            KC_B,    KC_N,   KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,        TT(GAMING),
                                               LT(NUM, KC_ESC), LT(EXT, KC_SPC), TAB_KEY, KC_ENT, OSL(SYM),    KC_BSPC
    ),

    [COLEMAK] = LAYOUT_split_3x6_3(
        _______, KC_Q,        KC_W,        KC_F,        KC_P,        KC_B,    KC_J,    KC_L,        KC_U,        KC_Y,        KC_QUOT,     _______,
        _______, GUI_T(KC_A), ALT_T(KC_R), CTL_T(KC_S), SFT_T(KC_T), KC_G,    KC_M,    SFT_T(KC_N), CTL_T(KC_E), ALT_T(KC_I), GUI_T(KC_O), _______,
        _______, KC_Z,        KC_X,        KC_C,        KC_D,        KC_V,    KC_K,    KC_H,        KC_COMM,     KC_DOT,      KC_SLSH,     _______,
                                           _______,     _______,     _______, _______, _______,     _______
    ),

    [GAMING] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E,            KC_R,   KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,     _______,
        KC_LCTL, KC_A, KC_S, KC_D,            KC_F,   KC_G,    KC_H,   KC_J,    KC_K,    KC_L,   KC_QUOTE, _______,
        KC_LSFT, KC_Z, KC_X, KC_C,            KC_V,   KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,  _______,
                             LT(NUM, KC_ESC), KC_SPC, KC_LALT, KC_ENT, KC_BSPC, MO(FUN)
    ),

    [EXT] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CW_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                   _______, _______, _______, _______, _______, _______
    ),

    [SYM] = LAYOUT_split_3x6_3(
        _______, KC_AT,   KC_LABK, KC_RABK, KC_PERC, XXXXXXX, KC_CIRC, KC_AMPR, KC_LBRC, KC_RBRC, KC_HASH, _______,
        _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_PIPE, KC_SCLN, KC_COLN, KC_LPRN, KC_RPRN, KC_DQUO, _______,
        _______, KC_TILD, KC_BSLS, KC_ASTR, KC_UNDS, XXXXXXX, KC_GRV,  KC_DLR,  KC_LCBR, KC_RCBR, KC_SLSH, _______,
                                   _______, _______, _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8,   KC_9, XXXXXXX, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX, KC_4, KC_5,   KC_6, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2,   KC_3, KC_DOT,  _______,
                                   _______, _______, _______, _______, KC_0, MO(FUN)
    ),

    [FUN] = LAYOUT_split_3x6_3(
        RM_TOGG, XXXXXXX, XXXXXXX, KC_MSTP, KC_PSCR, XXXXXXX, XXXXXXX, KC_F7,   KC_F8,  KC_F9, KC_F12, QK_BOOT,
        RM_NEXT, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRIU, XXXXXXX, KC_F4,   KC_F5,  KC_F6, KC_F11, QK_RBT,
        RM_PREV, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, KC_BRID, XXXXXXX, KC_F1,   KC_F2,  KC_F3, KC_F10, EE_CLR,
                                   _______, _______, _______, _______, _______, _______
    ),


#ifdef POINTING_DEVICE_ENABLE
    [MOUSE] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, HK_D_MODE, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, HK_S_MODE, HK_D_MODE, XXXXXXX, XXXXXXX,   MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______,   _______,   _______, MS_BTN1,   MS_BTN3, _______
    ),
#endif
};

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // QWERTY
        case CTL_T(KC_K):
        case SFT_T(KC_F):
        case SFT_T(KC_J):
        case RCTL_T(KC_K):
        // COLEMAK
        case CTL_T(KC_S):
        case SFT_T(KC_T):
        case SFT_T(KC_N):
        case RCTL_T(KC_E):
            return TAPPING_TERM - 40;

        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef FLOW_TAP_TERM
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record,
                           uint16_t prev_keycode) {
    // only allow flow tap when following a letter, not hotkeys
    if (get_tap_keycode(prev_keycode) <= KC_Z &&
        (get_mods() & MOD_MASK_CAG) == 0) {
        return FLOW_TAP_TERM;
    }

    return 0;  // disable flow tap otherwise
}
#endif

#ifdef CHORDAL_HOLD
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
        return true;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif

void set_layer_color(int layer) {
    hsv_t hsv = layer_colors[layer];
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
}

void keyboard_post_init_keymap(void) {
    set_layer_color(QWERTY);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    set_layer_color(layer);
    return state;
}

#if defined(OLED_ENABLE) && !defined(POINTING_DEVICE_ENABLE)
static const char* last_key_str = "None";

bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        last_key_str = get_keycode_string(keycode);
    }
    return true;
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a,
        0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0,
        0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab,
        0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1,
        0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc,
        0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}

void oled_render_layer(void) {
    static const char* layer_names[] = {
        [QWERTY] = "QWERTY", [COLEMAK] = "COLEMAK", [GAMING] = "GAMING",
        [EXT] = "EXT",       [SYM] = "SYM",         [NUM] = "NUM",
        [FUN] = "FUN",
#ifdef POINTING_DEVICE_ENABLE
        [MOUSE] = "MOUSE"
#endif
    };

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
        oled_render_logo();
    } else {
        oled_render_layer();
        oled_render_key();
        oled_render_mods();
    }

    return false;
}
#endif

