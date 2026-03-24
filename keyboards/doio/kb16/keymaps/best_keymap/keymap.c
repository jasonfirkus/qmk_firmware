/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

// OLED animation
#include "lib/layer_status/layer_status.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _FN,
    _FN1,
    _FN2
};

enum custom_keycodes {
    SCROLL_X2_UP = QK_USER,
    SCROLL_X2_DOWN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │ 1 │ 2 │ 3 │ 4 │   │Ply│ │TO1│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │ 5 │ 6 │ 7 │ 8 │
       ├───┼───┼───┼───┤
       │ 9 │ 0 │ ↑ │Ent│      ┌───┐
       ├───┼───┼───┼───┤      │Mut│
       │Fn2│ ← │ ↓ │ → │      └───┘
       └───┴───┴───┴───┘
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │ ! │ @ │ # │ $ │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │ % │ ^ │ & │ * │
       ├───┼───┼───┼───┤
       │ ( │ ) │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0         1        2        3         4      */
    [_BASE] = LAYOUT(
                A(KC_1),    A(KC_2),    A(KC_3),    A(KC_4),    G(KC_L),
                MC_5,       MC_6,       MC_7,       C(S(KC_I)), MC_3,
                MC_4,       MC_0,       C(KC_BSPC), C(KC_DEL),  KC_MPLY,
                S(KC_TAB),  KC_MPRV,    KC_MNXT,    A(KC_RGHT)
            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │   │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │   │   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4       */
    [_FN] = LAYOUT(
                S(KC_X),  S(KC_C), S(KC_V), KC_DEL,   LCA(KC_E),
                KC_V,     KC_A,    KC_Y,    KC_Q,     TO(_FN1),
                KC_P,     S(KC_GRV), KC_T,  KC_F7,    C(KC_S),
                S(KC_N),  S(KC_E), KC_R,    KC_S
            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │   │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │   │   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4       */
    [_FN1] = LAYOUT(
                C(KC_X),  C(KC_C), C(KC_V), KC_DEL,  C(KC_M),
                KC_V,     S(KC_A), KC_A,    KC_B,    TO(_FN2),
                KC_SPC,   KC_N,    KC_R,    KC_C,    C(KC_S),
                KC_P,     KC_H,    KC_LALT, KC_T
            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │Spi│Spd│   │   │   │   │ │TO0│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │Sai│Sad│   │   │
       ├───┼───┼───┼───┤
       │Tog│Mod│Hui│   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │Vai│Hud│Vad│      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        */
    [_FN2] = LAYOUT(
                C(KC_X), C(KC_C), C(KC_V), KC_DEL,  BL_BRTG,
                KC_G,    KC_S,    KC_F9,   S(KC_R), TO(_BASE),
                KC_R,    KC_X,    KC_Y,    KC_Z,    C(KC_S),
                KC_TAB,  KC_1,    KC_2,    KC_3
            ),
};

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();

        return true;
    }
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case SCROLL_X2_UP:
            tap_code(QK_MOUSE_WHEEL_UP);
            tap_code(QK_MOUSE_WHEEL_UP);
            tap_code(QK_MOUSE_WHEEL_UP);
            return false;
        case SCROLL_X2_DOWN:
            tap_code(QK_MOUSE_WHEEL_DOWN);
            tap_code(QK_MOUSE_WHEEL_DOWN);
            tap_code(QK_MOUSE_WHEEL_DOWN);
            return false;
    }

    return true;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(C(KC_PGUP), C(KC_PGDN)), ENCODER_CCW_CW(C(KC_LEFT), C(KC_RGHT)), ENCODER_CCW_CW(SCROLL_X2_UP, SCROLL_X2_DOWN) },
    [_FN]   = { ENCODER_CCW_CW(MS_WHLL, MS_WHLR), ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(C(KC_Z), C(S(KC_Z))) },
    [_FN1]  = { ENCODER_CCW_CW(MS_WHLL, MS_WHLR), ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(C(KC_Z), C(S(KC_Z))) },
    [_FN2]  = { ENCODER_CCW_CW(KC_LBRC, KC_RBRC), ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(C(KC_Z), C(S(KC_Z))) },
};
#endif
