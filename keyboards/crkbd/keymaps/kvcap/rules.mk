OLED_ENABLE = yes

#CONSOLE_ENABLE = no

#OLED_DRIVER_ENABLE = yes

#BACKLIGHT_ENABLE = no

RGB_MATRIX_DRIVER = ws2812

RGB_MATRIX_ENABLE = yes

RGBLIGHT_ENABLE = no

TAP_DANCE_ENABLE = yes
# necesario para ocupar el doble pulso (tap dance) en el keymap

#EXTRAKEY_ENABLE = yes 
# EXTRAKEY_ENABLE es necesario para ocupar los keycodes KC_MUTE, KC_VOLD y KC_VOLU

#MOUSEKEY_ENABLE = no

WPM_ENABLE = yes
# necesario para ocupar get_current_wpm()
# obtener el valor de words per mes

## ---------- For reduce size on Firmware ---------- ##
LTO_ENABLE = yes
EXTRAFLAGS += -flto

# CONSOLE_ENABLE = yes

# NKRO_ENABLE = yes

SPLIT_KEYBOARD = yes

SLEEP_LED_ENABLE = yes
