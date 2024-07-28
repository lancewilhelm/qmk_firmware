/* Copyright 2015-2021 Jack Humbert
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
#include "muse.h"

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Mute | Ctrl | Alt  | Cmd  |    Lower    |    Space    | Raise|  Cmd | Down |  Up  |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_grid(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT), KC_MPLY, XXXXXXX, XXXXXXX, KC_LCTL, KC_LGUI, LOWER, KC_SPC, KC_SPC, KC_LALT, RAISE, XXXXXXX, XXXXXXX),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |  Del |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  '   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |   _  |   +  |   {  |   }  |   |  |   -  |   =  |   [  |   ]  |   \  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | Rect | Rect | Rect |             |             |      |      | Prev | Next |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(KC_TILD, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______, KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______, LCA(KC_1), LCA(KC_5), LCA(KC_4), _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |  F1  |  F2  |  F3  |  F4  |  F5  |      | Home |  Up  |  End |      |  Del |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Del  |  F6  |  F7  |  F8  |  F9  |  F10 |      | Left | Down |Right |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | F11  | F12  | F13  | F14  | F15  |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | Rect | Rect | Rect |             |             |      |      | Prev | Next |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______, KC_HOME, KC_UP, KC_END, _______, KC_DEL, KC_DEL, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, QK_BOOT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, _______, LCA(KC_1), LCA(KC_5), LCA(KC_4), _______, _______, _______, LCA(KC_D), LCA(KC_F), LCA(KC_G), _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |NUMPAD| Reset|Debug | RGB  |RGBMOD|      |      | Home |  Up  |  End |      |  Del |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |QWERTY| HUE+ | SAT+ |BRGTH+|      |      | Left | Down |Right |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Colmak| HUE- | SAT- |BRGTH-|      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |             |             |      |      | Rect | Rect |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(_______, RESET, _______, RGB_TOG, RGB_MOD, _______, _______, KC_HOME, KC_UP, KC_END, _______, KC_DEL, _______, _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, LCA(KC_1), LCA(KC_5), LCA(KC_4), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LCA(KC_LEFT), LCA(KC_RIGHT)),
};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }

bool lctl_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
    //     case KC_LCTL:
    //         if (record->event.pressed) {
    //             lctl_pressed = true;
    //         } else {
    //             lctl_pressed = false;
    //         }
    //         return true;
    //         break;
    //     case QWERTY:
    //         if (record->event.pressed) {
    //             print("mode just switched to qwerty and this is a huge string\n");
    //             set_single_persistent_default_layer(_QWERTY);
    //         }
    //         return false;
    //         break;
    // }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(_ADJUST)) {
        if (clockwise) {
            rgblight_step();
        } else {
            rgblight_step_reverse();
        }
    } else if (IS_LAYER_ON(_RAISE)) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    } else if (lctl_pressed) {
        if (clockwise) {
            unregister_code(KC_LCTL);
            tap_code16(G(S(KC_Z)));
            register_code(KC_LCTL);
        } else {
            unregister_code(KC_LCTL);
            tap_code16(G(KC_Z));
            register_code(KC_LCTL);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_song);
                }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_gb_song);
                }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
