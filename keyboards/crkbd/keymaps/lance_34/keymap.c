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

// Layer enum, may be used later for some functions
enum corne_layers {
    _BASE,
    _SYM,
    _NAV,
    _NUM,
};

// Custom keycodes
// #define OSM_SFT OSM(MOD_LSFT)
// #define OSM_CTL OSM(MOD_LCTL)
// #define OSM_ALT OSM(MOD_LALT)
// #define OSM_GUI OSM(MOD_LGUI)

// enum for custom keycodes
enum custom_keycodes {
    OSM_CTL = SAFE_RANGE,
    OSM_ALT,
    OSM_GUI,
    OSM_SFT,
    SWP_WIN,
    TMUX_P
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
    //,-------------------------------------------------------                   |-------------------------------------------------------
        XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, KC_LSFT, TL_UPPR,    TL_LOWR,  KC_SPC, XXXXXXX
                                        //|--------+--------+--------|  |--------+--------+--------|
    ),

    [_SYM] = LAYOUT_split_3x6_3(
    //,-------------------------------------------------------                   |-------------------------------------------------------
        XXXXXXX, KC_LBRC, KC_LABK,  KC_EQL, KC_RABK, KC_RBRC,                      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_LCBR, KC_LPRN, KC_COLN, KC_RPRN, KC_RCBR,                      KC_SCLN, OSM_SFT, OSM_GUI, OSM_ALT, OSM_CTL, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_UNDS, KC_PLUS, KC_MINS, KC_AMPR, KC_PIPE,                      KC_CIRC, KC_BSLS, KC_ASTR, KC_TILD,  KC_GRV, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, KC_LSFT, _______,    _______,  KC_SPC, XXXXXXX
                                        //|--------+--------+--------|  |--------+--------+--------|
    ),

    [_NAV] = LAYOUT_split_3x6_3(
    //,-------------------------------------------------------                   |-------------------------------------------------------
        XXXXXXX, KC_TAB,  SWP_WIN, XXXXXXX,  TMUX_P, KC_VOLU,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, OSM_CTL, OSM_ALT, OSM_GUI, OSM_SFT, KC_VOLD,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_BSPC, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, RGB_MOD, XXXXXXX, XXXXXXX, KC_MPLY, KC_MNXT,                      CW_TOGG,  KC_ENT, XXXXXXX, XXXXXXX,  KC_ESC, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, KC_LSFT, _______,    _______,  KC_SPC, XXXXXXX
                                        //|--------+--------+--------|  |--------+--------+--------|
    ),

    [_NUM] = LAYOUT_split_3x6_3(
    //,-------------------------------------------------------                   |-------------------------------------------------------
        XXXXXXX,  KC_F12,   KC_F7,   KC_F8,   KC_F9, XXXXXXX,                      KC_MINS,    KC_7,    KC_8,    KC_9, KC_SLSH, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,                      KC_ASTR,    KC_4,    KC_5,    KC_6,    KC_0, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, XXXXXXX,                       KC_DOT,    KC_1,    KC_2,    KC_3, KC_PLUS, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                        //|--------+--------+--------|  |--------+--------+--------|
    ),
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _NUMSYM, _ARROWS, _ADJUST);
// }

bool swap_win_active = false;
bool tmux_pre_active = false;

void update_swapper(bool *active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}

bool handle_osm(uint16_t keycode, keyrecord_t *record, uint16_t kc, uint16_t mod_bit) {
    static uint16_t osm_timer = 0;
    if (record->event.pressed) {
        osm_timer = timer_read();
        register_code(kc);
    } else {
        unregister_code(kc);
        if (timer_elapsed(osm_timer) < TAPPING_TERM) {
            set_oneshot_mods(mod_bit);
        }
    }
    return false;
}

bool update_tmux(uint16_t keycode, keyrecord_t *record) {
    static uint16_t tmux_timer = 0;

    if (keycode == TMUX_P) {
        if (record->event.pressed) {
            tmux_pre_active = true;
            tmux_timer = timer_read();
        } else {
            if (tmux_pre_active && timer_elapsed(tmux_timer) < TAPPING_TERM) {
                // If released quickly, send Ctrl+Space
                // SEND_STRING(SS_LCTL(" "));
                register_code(KC_LCTL);
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_LCTL);
            }
            tmux_pre_active = false;
        }
    } else if (tmux_pre_active) {
        if (record->event.pressed) {
            // TMUX_KEY is being held, send Ctrl+Space followed by the pressed key
            // SEND_STRING(SS_LCTL(" "));
            register_code(KC_LCTL);
            register_code(KC_SPC);
            unregister_code(KC_SPC);
            unregister_code(KC_LCTL);
            tap_code(keycode);
            return false;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &swap_win_active, KC_LGUI, KC_TAB, SWP_WIN, keycode, record
    );
    if (!update_tmux(keycode, record)) {
        return false;
    }

    switch (keycode) {
        // Control One Shot Hold Modifier
        case OSM_CTL:
            return handle_osm(keycode, record, KC_LCTL, MOD_BIT(KC_LCTL));
        case OSM_ALT:
            return handle_osm(keycode, record, KC_LALT, MOD_BIT(KC_LALT));
        case OSM_GUI:
            return handle_osm(keycode, record, KC_LGUI, MOD_BIT(KC_LGUI));
        case OSM_SFT:
            return handle_osm(keycode, record, KC_LSFT, MOD_BIT(KC_LSFT));
    }
    return true;
}

// OLED CODE -------------------------------------------------
#ifdef OLED_ENABLE

#ifdef USE_OLED_COMPRESSION
static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i = 0; i < NUM_OLED_BYTES; i++) {
        uint8_t bit          = i % 8;
        uint8_t map_index    = i / 8;
        uint8_t _block_map   = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}
#endif //USE_OLED_COMPRESSION

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master() && !is_keyboard_left()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    } else if (!is_keyboard_master() && !is_keyboard_left()) {
        return OLED_ROTATION_270;
    } else if (!is_keyboard_master() && is_keyboard_left()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

#define L_BASE 0
#define L_NUMSYM 2
#define L_ARROWS 4
#define L_ADJUST 14

// Writes the current layer state on the screen wherever the cursor is
void render_layer_state(void) {
    if (oled_horizontal) {
        oled_set_cursor(0, 0);
    } else {
        oled_set_cursor(0, 15);
    }

    switch (layer_state) {
        case L_BASE :
            if (default_layer_state == 1) {
                oled_write_P(PSTR("QWERT"), false);
            } else {
                oled_write_P(PSTR("Colmk"), false);
            }
            break;
        case L_NUMSYM:
            oled_write_P(PSTR("NmSym"), false);
            break;
        case L_ARROWS:
            oled_write_P(PSTR("Arrws"), false);
            break;
        case L_ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
    }
}

// void oled_render_logo(void) {
//     #ifdef USE_OLED_COMPRESSION
//     oled_write_compressed_P(lance_logo_map, lance_logo_list);
//     #else
//     oled_write_raw_P(lance_logo, NUM_OLED_BYTES);
//     #endif //USE_OLED_COMPRESSION
// }

void animation_phase(void) {
    if (get_current_wpm() <= IDLE_SPEED) {
        current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
        uint8_t idx = abs((IDLE_FRAMES - 1) - current_idle_frame);
        #ifdef USE_OLED_COMPRESSION
        oled_write_compressed_P(idle_maps[idx], idle_lists[idx]);
        #else
        oled_write_raw_P(idle[idx], ANIM_SIZE);
        #endif //USE_OLED_COMPRESSION
    }
    if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
        #ifdef USE_OLED_COMPRESSION
        oled_write_compressed_P(prep_map, prep_list);
        #else
        oled_write_raw_P(prep[0], ANIM_SIZE);  // remove if IDLE_FRAMES >1
        // oled_write_raw_P(prep[abs((PREP_FRAMES-1)-current_prep_frame)], ANIM_SIZE);
        #endif //USE_OLED_COMPRESSION
    }
    if (get_current_wpm() >= TAP_SPEED) {
        current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
        uint8_t idx = abs((TAP_FRAMES - 1) - current_tap_frame);
        #ifdef USE_OLED_COMPRESSION
            oled_write_compressed_P(tap_maps[idx], tap_lists[idx]);
        #else
            oled_write_raw_P(tap[idx], ANIM_SIZE);
        #endif
    }
}

static void render_bongo_cat(void) {
    // assumes 1 frame prep stagen
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

// // Update WPM counters
// static void render_wpm_counters(int current_wpm) {
//     int cursorposition_cur = 2;
//     int cursorposition_max = 1;
//     if (oled_horizontal == false) {
//         cursorposition_cur = 13;
//         cursorposition_max = 14;
//     }
//
//     char wpm_counter[4];
//     wpm_counter[3] = '\0';
//     wpm_counter[2] = '0' + current_wpm % 10;
//     wpm_counter[1] = '0' + (current_wpm / 10) % 10;
//     wpm_counter[0] = '0' + (current_wpm / 100) % 10;
//     oled_set_cursor(0, cursorposition_cur);
//     oled_write(wpm_counter, false);
//
//     if (current_wpm > max_wpm) {
//         max_wpm = current_wpm;
//         wpm_limit = max_wpm + 20;
//         oled_set_cursor(0, cursorposition_max);
//         oled_write(wpm_counter, false);
//     }
// }

// // Toggles pixel on/off, converts horizontal coordinates to vertical equivalent if necessary
// static void write_pixel(int x, int y, bool onoff) {
//     oled_write_pixel(y, 127 - x, onoff);
//     // if (oled_horizontal) {
//     //     oled_write_pixel(x, y, onoff);
//     // } else {
//     //     oled_write_pixel(y, 127 - x, onoff);
//     // }
// }

// // Update WPM snail icon
// static void render_wpm_icon(int current_wpm) {
//     // wpm_icon is used to prevent unnecessary redraw
//     if ((current_wpm < icon_med_wpm) && (wpm_icon != 0)) {
//         wpm_icon = 0;
//     } else if ((current_wpm >= icon_med_wpm) && (current_wpm < icon_fast_wpm) && (wpm_icon != 1)) {
//         wpm_icon = 1;
//     } else if ((current_wpm >= icon_fast_wpm) && (wpm_icon != 2)) {
//         wpm_icon = 2;
//     } else {
//         return;
//     }
//     static const char PROGMEM snails[][2][24] = {
//         {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0xA0, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x50, 0x88, 0x04, 0x00, 0x00},
//          {0x40, 0x60, 0x50, 0x4E, 0x51, 0x64, 0x4A, 0x51, 0x54, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x40, 0x30, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00}},
//         {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x04, 0x98, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00},
//          {0x60, 0x50, 0x54, 0x4A, 0x51, 0x64, 0x4A, 0x51, 0x55, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x21, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00, 0x00}},
//         {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x10, 0x10, 0x10, 0x20, 0x40, 0x40, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00},
//          {0x60, 0x58, 0x54, 0x62, 0x49, 0x54, 0x52, 0x51, 0x55, 0x49, 0x62, 0x52, 0x4D, 0x45, 0x46, 0x22, 0x21, 0x11, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00}}
//     };
//     if (oled_horizontal) {
//         oled_set_cursor(3, 1);
//         oled_write_raw_P(snails[wpm_icon][0], sizeof(snails[wpm_icon][0]));
//         oled_set_cursor(3, 2);
//         oled_write_raw_P(snails[wpm_icon][1], sizeof(snails[wpm_icon][1]));
//     } else {
//         oled_set_cursor(0, 11);
//         oled_write_raw_P(snails[wpm_icon][0], sizeof(snails[wpm_icon][0]));
//         oled_set_cursor(0, 12);
//         oled_write_raw_P(snails[wpm_icon][1], sizeof(snails[wpm_icon][1]));
//     }
// }

static void render_lance(void) {
    // 'lancesigkeyboardtiny', 16x32px
    static const char PROGMEM lance_logo_l_1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM lance_logo_l_2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0xb6, 0xbe, 0xb6, 0xb6, 0x9c, 0x88, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM lance_logo_l_3[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0xed, 0x6d, 0x6d, 0x6d, 0xe7, 0xc3, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM lance_logo_l_4[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0x7b, 0x18, 0x38, 0x18, 0x7b, 0x7b, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM lance_logo_r_1[] = {0x00, 0x00, 0x00, 0x00, 0xde, 0xde, 0x18, 0x1c, 0x18, 0xde, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM lance_logo_r_2[] = {0x00, 0x00, 0x00, 0x00, 0xc3, 0xe7, 0xb6, 0xb6, 0xb6, 0xb7, 0xb3, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM lance_logo_r_3[] = {0x00, 0x00, 0x00, 0x00, 0x11, 0x39, 0x6d, 0x6d, 0x7d, 0x6d, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM lance_logo_r_4[] = {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00};

    if (is_keyboard_left()) {
        oled_set_cursor(1, 0);
        oled_write_raw_P(lance_logo_l_1, sizeof(lance_logo_l_1));
        oled_set_cursor(1, 1);
        oled_write_raw_P(lance_logo_l_2, sizeof(lance_logo_l_2));
        oled_set_cursor(1, 2);
        oled_write_raw_P(lance_logo_l_3, sizeof(lance_logo_l_3));
        oled_set_cursor(1, 3);
        oled_write_raw_P(lance_logo_l_4, sizeof(lance_logo_l_4));
    } else {
        oled_set_cursor(1, 0);
        oled_write_raw_P(lance_logo_r_1, sizeof(lance_logo_r_1));
        oled_set_cursor(1, 1);
        oled_write_raw_P(lance_logo_r_2, sizeof(lance_logo_r_2));
        oled_set_cursor(1, 2);
        oled_write_raw_P(lance_logo_r_3, sizeof(lance_logo_r_3));
        oled_set_cursor(1, 3);
        oled_write_raw_P(lance_logo_r_4, sizeof(lance_logo_r_4));
    }
}

// // Update WPM graph
// static void render_wpm_graph(int current_wpm) {
//     int line_height = ((current_wpm / graph_top_wpm) * 7);
//     if (line_height > 7) {
//         line_height = 7;
//     }
//     // Count graph line pixels, return if nothing to draw
//     int pixel_count = line_height;
//     for (int i = 0; i < 63; i++) {
//         pixel_count += graph_lines[i];
//     }
//     if (pixel_count == 0) {
//         return;
//     }
//     // Shift array elements left or right depending on graph_direction, append new graph line
//     if (graph_direction) {
//         for (int i = 0; i < 63; i++) {
//             graph_lines[i] = graph_lines[i + 1];
//         }
//         graph_lines[63] = line_height;
//     } else {
//         for (int i = 63; i > 0; i--) {
//             graph_lines[i] = graph_lines[i - 1];
//         }
//         graph_lines[0] = line_height;
//     }
//     // Draw all graph lines (left to right, bottom to top)
//     int draw_count, arrpos;
//     for (int x = 1; x <= 127; x += 2) {
//         arrpos = x / 2;
//         draw_count = graph_lines[arrpos];
//         for (int y = 31; y >= 25; y--) {
//             if (draw_count > 0) {
//                 write_pixel(x, y, true);
//                 draw_count--;
//             } else {
//                 write_pixel(x, y, false);
//             }
//         }
//     }
// }

bool oled_task_user(void) {
    // int current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        render_bongo_cat();
        render_lance();
    } else {
        // oled_render_logo();
        // render_wpm(current_wpm);
        // Update the layer state
        // render_layer_state();
        // Update WPM counters
        // render_wpm_counters(current_wpm);
        // Update WPM snail icon
        // render_wpm_icon(current_wpm);
        // Update WPM graph every graph_refresh milliseconds
        // if (timer_elapsed(timer) > graph_refresh) {
        //     render_wpm_graph(current_wpm);
        //     timer = timer_read();
        // }
    }
    return false;
}

#endif // OLED_ENABLE
