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

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "oled_utils.h"

enum corne_layers {
    _QWERTY,
    _COLEMAK,
    _NUMSYM,
    _ARROWS,
    _ADJUST
};

enum corne_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK
};

#define NUMSYM MO(_NUMSYM)
#define ARROWS MO(_ARROWS)

char wpm_str[10];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y,  KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      KC_LCTL, KC_LGUI,  NUMSYM,            KC_SPC,   KC_LALT, ARROWS
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  RSFT_T(KC_ENT),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      KC_LCTL, KC_LGUI,  NUMSYM,            KC_SPC,   KC_LALT, ARROWS
                                      //`--------------------------'  `--------------------------'

  ),

  [_NUMSYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_UNDS,  KC_PLUS,KC_LCBR, KC_RCBR, KC_PIPE,                      KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      KC_LCTL, KC_LGUI,  _______,            KC_SPC,   KC_LALT, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_ARROWS] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                      XXXXXXX, KC_HOME, KC_UP, KC_END, XXXXXXX, KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LCTL, KC_LGUI,  _______,            KC_SPC,   KC_LALT, _______
                                        //`--------------------------'  `--------------------------'
  ),
  
    [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,   DEBUG, XXXXXXX, XXXXXXX, XXXXXXX,  QWERTY,                      COLEMAK, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX, CG_TOGG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      XXXXXXX, KC_MPLY, KC_VOLD, KC_MNXT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX, LCA(KC_1), LCA(KC_5), LCA(KC_4), XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    KC_LCTL, KC_LGUI,  _______,            KC_SPC,   KC_LALT, _______
                                      //`--------------------------'  `--------------------------'
  ),  

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUMSYM, _ARROWS, _ADJUST); 
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // if (record->event.pressed) {
        // dprintf("key pressed, %lu\n", layer_state);    }
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
    }
    return true;
}

#ifdef OLED_ENABLE
// Code containing pixel art, contains:
// 5 idle frames, 1 prep frame, and 2 tap frames

// To make your own pixel art:
// save a png/jpeg of an 128x32 image (resource: https://www.pixilart.com/draw )
// follow this guide up to and including "CONVERT YOUR IMAGE" https://docs.splitkb.com/hc/en-us/articles/360013811280-How-do-I-convert-an-image-for-use-on-an-OLED-display-
// replace numbers in brackets with your own
// if you start getting errors when compiling make sure you didn't accedentally delete a bracket

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_NUMSYM 4
#define L_ARROWS 8
#define L_ADJUST 28

void oled_render_layer_state(void) {
    // oled_write_P(PSTR("Layer: "), false);

    switch (layer_state) {
        case L_BASE :
            if (default_layer_state == 1) {
                oled_write_P(PSTR("QWERTY"), false);
            } else {
                oled_write_P(PSTR("Colemak"), false);
            }

            break;
        case L_NUMSYM:
            oled_write_P(PSTR("NumSym"), false);
            break;
        case L_ARROWS:
            oled_write_P(PSTR("Arrows"), false);
            break;
        case L_ADJUST:
            oled_write_P(PSTR("Adjust"), false);
            break;
    }
}

void oled_render_logo(void) {
    oled_write_raw_P(lance_logo, sizeof(lance_logo));
}

// Code containing pixel art, contains:
// 5 idle frames, 1 prep frame, and 2 tap frames

// To make your own pixel art:
// save a png/jpeg of an 128x32 image (resource: https://www.pixilart.com/draw )
// follow this guide up to and including "CONVERT YOUR IMAGE" https://docs.splitkb.com/hc/en-us/articles/360013811280-How-do-I-convert-an-image-for-use-on-an-OLED-display-
// replace numbers in brackets with your own
// if you start getting errors when compiling make sure you didn't accedentally delete a bracket
static void render_anim(void) {
    

    // assumes 1 frame prep stage
    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
        }
        if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
            // oled_write_raw_P(prep[abs((PREP_FRAMES-1)-current_prep_frame)], ANIM_SIZE); // uncomment if IDLE_FRAMES >1
            oled_write_raw_P(prep[0], ANIM_SIZE);  // remove if IDLE_FRAMES >1
        }
        if (get_current_wpm() >= TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIM_SIZE);
        }
    }
    if (get_current_wpm() != 000) {
        oled_on();  // not essential but turns on animation OLED with any alpha keypress
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_anim();  // renders pixelart
        oled_set_cursor(0, 0);                            // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
        oled_render_layer_state();
        // sprintf(wpm_str, "WPM:%03d", get_current_wpm());  // edit the string to change wwhat shows up, edit %03d to change how many digits show up
        // oled_write(wpm_str, false);                       // writes wpm on top left corner of string
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
