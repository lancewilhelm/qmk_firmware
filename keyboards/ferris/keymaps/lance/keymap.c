// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Layer enum, may be used later for some functions
enum layers {
    _BASE,
    _SYM,
    _NAV,
    _NUM,
};

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
  [_BASE] = LAYOUT(
    //,----------------------------------------------                   |---------------------------------------------|--
           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
                                            KC_LSFT, TL_UPPR,    TL_LOWR,  KC_SPC
                                        //|--------+--------|  |--------+--------|
    ),

  [_SYM] = LAYOUT(
    //,----------------------------------------------                   |----------------------------------------------
        KC_LBRC, KC_LABK,  KC_EQL, KC_RABK, KC_RBRC,                      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        KC_LCBR, KC_LPRN, KC_COLN, KC_RPRN, KC_RCBR,                      KC_SCLN, OSM_SFT, OSM_GUI, OSM_ALT, OSM_CTL,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        KC_UNDS, KC_PLUS, KC_MINS, KC_AMPR, KC_PIPE,                      KC_CIRC, KC_BSLS, KC_ASTR, KC_TILD,  KC_GRV,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                            KC_LSFT, _______,    _______,  KC_SPC
                                        //|--------+--------|  |--------+--------|
    ),

  [_NAV] = LAYOUT(
    //,----------------------------------------------                   |----------------------------------------------
        KC_TAB,  SWP_WIN, XXXXXXX,  TMUX_P, KC_VOLU,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        OSM_CTL, OSM_ALT, OSM_GUI, OSM_SFT, KC_VOLD,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_BSPC,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        RGB_MOD, XXXXXXX, XXXXXXX, KC_MPLY, KC_MNXT,                      CW_TOGG,  KC_ENT, XXXXXXX, XXXXXXX,  KC_ESC,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                            KC_LSFT, _______,    _______,  KC_SPC
                                        //|--------+--------|  |--------+--------|
    ),

  [_NUM] = LAYOUT(
    //,----------------------------------------------                   |----------------------------------------------
         KC_F12,   KC_F7,   KC_F8,   KC_F9, XXXXXXX,                      KC_MINS,    KC_7,    KC_8,    KC_9, KC_SLSH,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_F11,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,                      KC_ASTR,    KC_4,    KC_5,    KC_6,    KC_0,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_F10,   KC_F1,   KC_F2,   KC_F3, XXXXXXX,                       KC_DOT,    KC_1,    KC_2,    KC_3, KC_PLUS,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
                                        //|--------+--------|  |--------+--------|
    ),
};

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
