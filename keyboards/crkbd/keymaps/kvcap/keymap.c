#include QMK_KEYBOARD_H
#define ANIM_FRAME_DURATION 200

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
    extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
    static uint32_t oled_timer = 0;
#endif

// extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Custom keycodes for layer keys
// Dual function escape with left command


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MACRO1,
  MACRO2
};

enum {
    TD_PC,
    TD_COMI,
    TD_SLA,
    TD_CAPLOCK,
    TD_ALT,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ;, twice for :
    [TD_PC] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
    [TD_COMI] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),
    [TD_SLA] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, LSFT(KC_SLSH)),
    [TD_CAPLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_LALT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,  TD(TD_PC), KC_LBRC,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     TD(TD_CAPLOCK), KC_Z, KC_X,  KC_C,  KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_SLA),KC_DEL,
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, LOWER, KC_SPC,     KC_ENT, RAISE, TD(TD_ALT)
                                      //|--------------------------|  |--------------------------|
  ), 
  [_LOWER] = LAYOUT(
  //|-----------------------------------------------------|                 |-----------------------------------------------------|
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+--------+--------|
    KC_TAB,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR,                   XXXXXXX, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                 --------+--------+--------+--------+--------+--------|
   TD(TD_CAPLOCK),KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  ,KC_TRNS,              KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS,  KC_TRNS, KC_DEL,
  //|------------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
                                    LCTL(KC_LALT), KC_TRNS, KC_ENT,      KC_SPC, ADJUST, KC_RALT
                                      //|--------------------------|    |--------------------------|
  ),                                //la tecla ssig control mas alt y lo que venga

  [_RAISE] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_EXLM,  KC_AT,   KC_HASH, KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_NUBS, XXXXXXX,   XXXXXXX, XXXXXXX, KC_END , XXXXXXX,                      KC_MINS, KC_QUOT, KC_NUHS,  KC_RBRC, KC_PIPE, KC_PLUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
TD(TD_CAPLOCK),XXXXXXX, XXXXXXX, XXXXXXX,KC_HOME, XXXXXXX,                      KC_UNDS, KC_EQL, KC_LCBR, KC_RCBR, KC_BSLS, KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, ADJUST, KC_SPC,      KC_ENT, KC_TRNS, KC_RALT 
                                      //|--------------------------|  |--------------------------|
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
      KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,  KC_F9,    KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     RGB_TOG, RGB_HUI, XXXXXXX, XXXXXXX, RGB_SPI, RGB_MOD,            KC_AUDIO_VOL_UP,    XXXXXXX, KC_UP,   KC_DEL, KC_LALT, KC_LCTL,  
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, RGB_HUD, XXXXXXX, XXXXXXX, RGB_SPD, XXXXXXX,            KC_AUDIO_VOL_DOWN, KC_LEFT,  KC_DOWN, KC_RGHT, XXXXXXX, KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, KC_TRNS, KC_SPC,    KC_ENT, KC_TRNS, KC_RALT 
                                      //|--------------------------|  |--------------------------|
  )
};

// ------------------------ VARIABLES --------------------------

uint8_t mod_state;
bool key_registered;

uint32_t master_sleep;
uint32_t slave_sleep;

uint8_t current_wpm = 0;
uint8_t current_mode;

int RGB_current_mode;

uint32_t anim_fishing_timer;
uint32_t anim_ghost_timer;
uint8_t current_fishing_frame = 0;
uint8_t current_ghost_frame = 0;

// -------------------------------------------------------------

#if defined RGB_MATRIX_ENABLE

    /* const int            led_count = 12;
    int                  leds[]    = {0, 1, 2, 3, 4, 5, 27, 28, 29, 30, 31, 32}; */
    const int            led_count = 53;
    int                  leds[]    = {0, 1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27, 28, 29, 30, 31, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    /* const int            led_count = 12;
    int                  leds[]    = {0, 1, 2, 3, 4, 5, 27, 28, 29, 30, 31, 32};

    const int            led_count = 6;
    int                  leds[]    = {0, 1, 2, 3, 4, 5}; */

    void set_rgblight_by_layer(uint32_t layer) {
        for (int i = 0; i < led_count; i++) {
            switch (layer) {
                case _LOWER:
                    rgb_matrix_set_color(leds[i], RGB_PURPLE);
                    break;
                case _RAISE:
                    rgb_matrix_set_color(leds[i], RGB_YELLOW);
                    break;
                case _ADJUST:
                    rgb_matrix_set_color(leds[i], RGB_GREEN);
                    break;
                default:
                    rgb_matrix_set_color(leds[i], RGB_SPRINGGREEN);
                    break;
            }
        }
    }

    void set_current_layer_rgb(void) {
        set_rgblight_by_layer(get_highest_layer(layer_state | default_layer_state));
    }

    bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) { 
        if (host_keyboard_led_state().caps_lock) {
            for (uint8_t i = led_min; i < led_max; i++) {
                if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                    rgb_matrix_set_color(i, RGB_RED);
                }
            }
        } else if (!host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color_all(RGB_OFF);
        }

        uint8_t mods                = get_mods();
        uint8_t oneshot_mods        = get_oneshot_mods();
        uint8_t oneshot_locked_mods = get_oneshot_locked_mods();

        bool isShift = mods & MOD_MASK_SHIFT || oneshot_mods & MOD_MASK_SHIFT || oneshot_locked_mods & MOD_MASK_SHIFT;
        bool isCtrl  = mods & MOD_MASK_CTRL || oneshot_mods & MOD_MASK_CTRL || oneshot_locked_mods & MOD_MASK_CTRL;
        bool isAlt   = mods & MOD_MASK_ALT || oneshot_mods & MOD_MASK_ALT || oneshot_locked_mods & MOD_MASK_ALT;
        bool isGui   = mods & MOD_MASK_GUI || oneshot_mods & MOD_MASK_GUI || oneshot_locked_mods & MOD_MASK_GUI;

        for (int i = 0; i < led_count; i++) {
            if (isShift) {
                rgb_matrix_set_color(leds[i], RGB_TEAL);
            } else if (isCtrl || isAlt || isGui) {
                rgb_matrix_set_color(leds[i], RGB_WHITE);
            } else {
                set_current_layer_rgb();
            }
        }
        return false;
    }

#endif

#if defined OLED_ENABLE
    oled_rotation_t oled_init_user(oled_rotation_t rotation) { 
        if (is_keyboard_master()) {
            return OLED_ROTATION_270;
        } else {
            return OLED_ROTATION_270; 
        }
        return rotation;
    }

    void render_space(void) {
        oled_write_P(PSTR("     "), false);
    }

    static void master_render_ghost(void) {
        static const char PROGMEM troll[2][128] = { // frames de troll       
            { // 'troll1' 32x28px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 
                0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x20, 0xd0, 0x08, 0x04, 0x02, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7c, 
                0x7c, 0x44, 0x00, 0x00, 0x88, 0xf8, 0xf8, 0x70, 0x01, 0x02, 0x04, 0x18, 0xe0, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x33, 0x4c, 0x80, 0x1e, 0x21, 0x20, 0x10, 0x00, 0x00, 0x18, 0x1e, 0x3c, 0x78, 
                0x78, 0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0x78, 0x3c, 0x0e, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 
                0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
            }, { // 'troll2' 32x28px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 
                0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x20, 0xd0, 0x08, 0x84, 0x42, 0x41, 0x40, 0x80, 0x00, 0x00, 0x00, 0x38, 0x7c, 
                0x7c, 0x44, 0x00, 0x00, 0x88, 0xf8, 0xf8, 0x70, 0x01, 0x02, 0x04, 0x18, 0xe0, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x33, 0x4c, 0x80, 0x03, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x18, 
                0x18, 0x38, 0x38, 0x38, 0x38, 0x38, 0x18, 0x0c, 0x06, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 
                0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        };

        void animate_ghost(void) {

            current_ghost_frame = (current_ghost_frame + 1) % 2; // current_ghost_frame se va turnando entre los valores 0 y 1    
            oled_write_raw_P(troll[abs(1 - current_ghost_frame)], 128);
        }

        if (timer_elapsed32(anim_ghost_timer) > ANIM_FRAME_DURATION) { 
            
            anim_ghost_timer = timer_read32(); // se actualiza anim_ghost_timer
            animate_ghost(); // se ejecuta animate_ghost()
        }

        if (current_wpm != 0) { 
            master_sleep = timer_read32(); 
        }      
    }

    static void slave_render_ghost(void) {
        static const char PROGMEM fishing[2][416] = { // frames de fishing
            { // 'fishing1' 32x100px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 
                0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x50, 0x88, 0x08, 0x10, 0x28, 0x44, 0xa8, 0x10, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7c, 0x82, 0x01, 0x61, 0x01, 0x02, 
                0x84, 0x48, 0x84, 0x02, 0x61, 0x01, 0x02, 0x84, 0x78, 0x00, 0x03, 0x0c, 0x32, 0xc1, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x08, 0x06, 0x01, 0x08, 0x90, 0x61, 0x02, 0x02, 0x01, 
                0x00, 0x00, 0x00, 0x01, 0x82, 0x82, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 
                0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x02, 0x0e, 0x11, 0x21, 0x20, 0x20, 0x40, 0x82, 0xff, 
                0x02, 0x00, 0x0e, 0x11, 0x20, 0x20, 0x40, 0x01, 0x81, 0x82, 0x42, 0x44, 0x40, 0x20, 0x3f, 0x40, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 
                0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
                0x00, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0xfd, 
                0x01, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x30, 0xc0, 0x00, 0xf8, 0x04, 0x02, 0x01, 0x01, 0x31, 
                0x49, 0x85, 0x92, 0x68, 0x08, 0x08, 0x10, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xc0, 0x81, 0x00, 0xc0, 0xf0, 0xf0, 0xf8, 0x88, 
                0x00, 0x20, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x08, 0x10, 0x13, 0x27, 0x4f, 0x5f, 0x5f, 0x5f, 0x5f, 
                0x5f, 0x5f, 0x5f, 0x4f, 0x27, 0x13, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            }, { // 'fishing2' 32x100px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 
                0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x50, 0x88, 0x08, 0x10, 0x28, 0x44, 0xa8, 0x10, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7c, 0x82, 0x01, 0x61, 0x01, 0x02, 
                0x84, 0x48, 0x84, 0x02, 0x61, 0x01, 0x02, 0x84, 0x78, 0x00, 0x03, 0x0c, 0x32, 0xc1, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x08, 0x06, 0x01, 0x08, 0x90, 0x61, 0x02, 0x02, 0x01, 
                0x00, 0x00, 0x00, 0x01, 0x82, 0x82, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 
                0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x02, 0x0e, 0x11, 0x21, 0x20, 0x20, 0x40, 0x82, 0xff, 
                0x02, 0x00, 0x0e, 0x11, 0x20, 0x20, 0x40, 0x01, 0x81, 0x82, 0x42, 0x44, 0x40, 0x20, 0x3f, 0x40, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 
                0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
                0x00, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0xfd, 
                0x01, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf9, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0xd0, 0x30, 0x01, 0x82, 0x64, 0x18, 0x00, 0x00, 0x00, 
                0x01, 0x06, 0x18, 0xe0, 0x00, 0x00, 0xc0, 0x30, 0x08, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x01, 0xc2, 0xe2, 0x21, 0x00, 0x80, 0xc4, 0xfc, 0xf8, 
                0xf0, 0xc0, 0x00, 0x00, 0x01, 0xc1, 0xf0, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x08, 0x11, 0x13, 0x26, 0x4e, 0x5f, 0x5f, 0x5f, 0x5f, 
                0x5f, 0x5f, 0x5e, 0x5e, 0x4f, 0x27, 0x11, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        };  
        
        void animate_fishing(void) {
        
            current_fishing_frame = (current_fishing_frame + 1) % 2; // current_ghost_frame se va turnando entre los valores 0 y 1
            oled_write_raw_P(fishing[abs(1 - current_fishing_frame)], 416); // fishing                                       
        }
        

        if (timer_elapsed32(anim_fishing_timer) > ANIM_FRAME_DURATION) { // timer_elapsed32(anim_fishing_timer) tiempo transcurrido en ms desde la ultima vez que se actualizo anim_ghost_timer
            
            anim_fishing_timer = timer_read32(); // se actualiza anim_ghost_timer
            animate_fishing(); // se ejecuta animate_ghost()
        }      

        if (current_wpm != 0) { 
            slave_sleep = timer_read32(); 
        }
    }

    void render_mod_status_gui_alt(uint8_t modifiers) {
        static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
        static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
        static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
        static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

        static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
        static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
        static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
        static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

        // fillers between the modifier icons bleed into the icon frames
        static const char PROGMEM off_off_1[] = {0xc5, 0};
        static const char PROGMEM off_off_2[] = {0xc6, 0};
        static const char PROGMEM on_off_1[] = {0xc7, 0};
        static const char PROGMEM on_off_2[] = {0xc8, 0};
        static const char PROGMEM off_on_1[] = {0xc9, 0};
        static const char PROGMEM off_on_2[] = {0xca, 0};
        static const char PROGMEM on_on_1[] = {0xcb, 0};
        static const char PROGMEM on_on_2[] = {0xcc, 0};

        if(modifiers & MOD_MASK_GUI) {
            oled_write_P(gui_on_1, false);
        } else {
            oled_write_P(gui_off_1, false);
        }

        if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
            oled_write_P(on_on_1, false);
        } else if(modifiers & MOD_MASK_GUI) {
            oled_write_P(on_off_1, false);
        } else if(modifiers & MOD_MASK_ALT) {
            oled_write_P(off_on_1, false);
        } else {
            oled_write_P(off_off_1, false);
        }

        if(modifiers & MOD_MASK_ALT) {
            oled_write_P(alt_on_1, false);
        } else {
            oled_write_P(alt_off_1, false);
        }

        if(modifiers & MOD_MASK_GUI) {
            oled_write_P(gui_on_2, false);
        } else {
            oled_write_P(gui_off_2, false);
        }

        if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
            oled_write_P(on_on_2, false);
        } else if(modifiers & MOD_MASK_GUI) {
            oled_write_P(on_off_2, false);
        } else if(modifiers & MOD_MASK_ALT) {
            oled_write_P(off_on_2, false);
        } else {
            oled_write_P(off_off_2, false);
        }

        if(modifiers & MOD_MASK_ALT) {
            oled_write_P(alt_on_2, false);
        } else {
            oled_write_P(alt_off_2, false);
        }
    }

    void render_mod_status_ctrl_shift(uint8_t modifiers) {
        static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
        static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
        static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
        static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

        static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
        static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
        static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
        static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

        // fillers between the modifier icons bleed into the icon frames
        static const char PROGMEM off_off_1[] = {0xc5, 0};
        static const char PROGMEM off_off_2[] = {0xc6, 0};
        static const char PROGMEM on_off_1[] = {0xc7, 0};
        static const char PROGMEM on_off_2[] = {0xc8, 0};
        static const char PROGMEM off_on_1[] = {0xc9, 0};
        static const char PROGMEM off_on_2[] = {0xca, 0};
        static const char PROGMEM on_on_1[] = {0xcb, 0};
        static const char PROGMEM on_on_2[] = {0xcc, 0};

        if(modifiers & MOD_MASK_CTRL) {
            oled_write_P(ctrl_on_1, false);
        } else {
            oled_write_P(ctrl_off_1, false);
        }

        if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
            oled_write_P(on_on_1, false);
        } else if(modifiers & MOD_MASK_CTRL) {
            oled_write_P(on_off_1, false);
        } else if(modifiers & MOD_MASK_SHIFT) {
            oled_write_P(off_on_1, false);
        } else {
            oled_write_P(off_off_1, false);
        }

        if(modifiers & MOD_MASK_SHIFT) {
            oled_write_P(shift_on_1, false);
        } else {
            oled_write_P(shift_off_1, false);
        }

        if(modifiers & MOD_MASK_CTRL) {
            oled_write_P(ctrl_on_2, false);
        } else {
            oled_write_P(ctrl_off_2, false);
        }

        if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
            oled_write_P(on_on_2, false);
        } else if(modifiers & MOD_MASK_CTRL) {
            oled_write_P(on_off_2, false);
        } else if(modifiers & MOD_MASK_SHIFT) {
            oled_write_P(off_on_2, false);
        } else {
            oled_write_P(off_off_2, false);
        }

        if(modifiers & MOD_MASK_SHIFT) {
            oled_write_P(shift_on_2, false);
        } else {
            oled_write_P(shift_off_2, false);
        }
    }

    void render_layer_state(void) {
        static const char PROGMEM default_layer[] = {
            0x20, 0x94, 0x95, 0x96, 0x20,
            0x20, 0xb4, 0xb5, 0xb6, 0x20,
            0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
        static const char PROGMEM raise_layer[] = {
            0x20, 0x97, 0x98, 0x99, 0x20,
            0x20, 0xb7, 0xb8, 0xb9, 0x20,
            0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
        static const char PROGMEM lower_layer[] = {
            0x20, 0x9a, 0x9b, 0x9c, 0x20,
            0x20, 0xba, 0xbb, 0xbc, 0x20,
            0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
        static const char PROGMEM adjust_layer[] = {
            0x20, 0x9d, 0x9e, 0x9f, 0x20,
            0x20, 0xbd, 0xbe, 0xbf, 0x20,
            0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
        if(layer_state_is(_ADJUST)) {
            oled_write_P(adjust_layer, false);
        } else if(layer_state_is(_LOWER)) {
            oled_write_P(lower_layer, false);
        } else if(layer_state_is(_RAISE)) {
            oled_write_P(raise_layer, false);
        } else {
            oled_write_P(default_layer, false);
        }
    }

    void render_status_main(void) {
        render_layer_state();
        render_space();
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    }

    void render_status_secondary(void) {
        slave_render_ghost();
        // slave_logo();
    }

    bool oled_task_user(void) {
        current_wpm = get_current_wpm();
        if ( timer_elapsed32(master_sleep) > 60000 && timer_elapsed32(slave_sleep) > 60000 && current_wpm == 0 ) {
            if (is_oled_on()) {
                oled_off();
            }
            timer_init();
            return false;
        }

        if (current_wpm != 0 && !is_oled_on()) {
            oled_on();
        }    

        if (is_keyboard_master()) {
            master_render_ghost();
            oled_set_cursor(0,5);
            oled_write_P(PSTR("KVCap"), false);
            oled_set_cursor(0,7);
            render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        } else {
            render_status_secondary();
            oled_set_cursor(0,12);
            oled_write_P(PSTR("crkbd"), false);
            oled_write_P(PSTR("ghost"), false);
        }
        return false;
    }

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        if (record->event.pressed) {
            #ifdef OLED_DRIVER_ENABLE
                oled_timer = timer_read32();
            #endif
        }

        switch (keycode) {
            case LOWER:
                if (record->event.pressed) {
                    layer_on(_LOWER);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                } else {
                    layer_off(_LOWER);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                }
                return false;
            case RAISE:
                if (record->event.pressed) {
                    layer_on(_RAISE);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                } else {
                    layer_off(_RAISE);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                }
                return false;
            case ADJUST:
                if (record->event.pressed) {
                    layer_on(_ADJUST);
                } else {
                    layer_off(_ADJUST);
                }
                return false;
            case MACRO1:
            if (record->event.pressed) {
                    SEND_STRING("");
                } else {
                    
                }
                return false;
            case MACRO2:
                if (record->event.pressed) {
                    SEND_STRING("");
                } else {
                    
                }
                return false;
                #ifdef RGB_MATRIX_ENABLE
                    if (record->event.pressed) {
                        eeconfig_update_rgb_matrix_default();
                        rgb_matrix_enable();
                    }
                #endif
                break;
        }
        return true;
    }
#endif

#if defined RGB_MATRIX_ENABLE
    void suspend_power_down_user(void) {
        rgb_matrix_set_suspend_state(true);
    }
    void suspend_wakeup_init_user(void) {
        rgb_matrix_set_suspend_state(false);
    }
#endif
