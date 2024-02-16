/* Copyright 2024 Hoang Nguyen (@isoamyl50)
 *
 * This file is part of the QMK Firmware
 *
 * The QMK Firmware is free software: you can redistribute it and/or modify
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

/* Keymaps and craps */
#define MAX_LAYERS 3

enum layer_names {
    _MEDIA_CONTROL,
    _NUMPAD,
    _PARALYZED,
    _KB_FN,
};

// Keep track of the current layer
static uint8_t current_layer = 0;

enum custom_keycodes {
    CC_FUNC = SAFE_RANGE,
    CC_NEXT_LAYER,
    CC_PREV_LAYER,
    CC_OLED_LGHT,
    CC_OLED_DARK,
};

// Keep track of if CC_FUNC is pressed
static bool cc_func_pressed = false;

void keyboard_pre_init_user(void) {
    setPinOutput(GP25);
    // writePinHigh(GP25);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Media control

     *  +---+---+---+
     *  |VOL|ESC|fun|
     *  +---+---+---+
     *  |I< |II>|>I |
     *  +---+---+---+
     *  | C | T | F |
     *  +---+---+---+
     *  | < | _ | > |
     *  +---+---+---+
     */
    [_MEDIA_CONTROL] = LAYOUT(
        KC_NO,      KC_ESC,     CC_FUNC,    KC_MUTE,
        KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,
        KC_C,       KC_T,       KC_F,       KC_MUTE,
        KC_LEFT,    KC_SPC,     KC_RGHT,    KC_MUTE
    ),
    /*
     * Numpad
     *
     *  +---+---+---+
     *  |...| 0 |...|
     *  +---+---+---+
     *  | 7 | 8 | 9 |
     *  +---+---+---+
     *  | 4 | 5 | 6 |
     *  +---+---+---+
     *  | 1 | 2 | 3 |
     *  +---+---+---+
     */
    [_NUMPAD] = LAYOUT(
        KC_NO,  KC_0,   KC_TRNS,    KC_TRNS,
        KC_7,   KC_8,   KC_9,       KC_TRNS,
        KC_4,   KC_5,   KC_6,       KC_TRNS,
        KC_1,   KC_2,   KC_3,       KC_TRNS
    ),
    /* FN key */
    [_KB_FN] = LAYOUT(
        KC_NO,   CC_OLED_LGHT,   KC_TRNS, QK_REBOOT,
        CC_OLED_DARK,   KC_NO,   KC_NO,   QK_REBOOT,
        KC_NO,   KC_NO,   KC_NO,   QK_REBOOT,
        KC_NO,   KC_NO,   KC_NO,   QK_REBOOT
    ),
    /* Paralyzed  */
    [_PARALYZED] = LAYOUT(
        KC_NO,   KC_NO,   KC_TRNS, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        /* Function key */
        case CC_FUNC:
            if (record->event.pressed) {
                layer_move(_KB_FN);
                cc_func_pressed = true;
            } else {
                layer_move(current_layer);
                cc_func_pressed = false;
            }
            return false;  // Skip all further processing of this key
        case CC_PREV_LAYER:
            if (record->event.pressed) {
                // Decrement the current layer, wrapping around to MAX_LAYERS - 1 when we reach the beginning
                current_layer = (current_layer - 1 + MAX_LAYERS) % MAX_LAYERS;
            }
            return false;
        case CC_NEXT_LAYER:
            if (record->event.pressed) {
                // Increment the current layer, wrapping around to 0 when we reach the end
                current_layer = (current_layer + 1) % MAX_LAYERS;
            }
            return false;
        #ifdef OLED_ENABLE
        case CC_OLED_DARK:
            if (record->event.pressed) {
                // Decrease brightness by 15, but not below 0
                uint8_t current_brightness = oled_get_brightness();
                if (current_brightness > 15) {
                    oled_set_brightness(current_brightness - 15);
                } else {
                    oled_set_brightness(0);
                }
            }
            return false;  // We handled this keypress
        case CC_OLED_LGHT:
            if (record->event.pressed) {
                // Increase brightness by 15, but not above 255
                uint8_t current_brightness = oled_get_brightness();
                if (current_brightness < 240) {
                    oled_set_brightness(current_brightness + 15);
                } else {
                    oled_set_brightness(255);
                }
            }
            return false;  // We handled this keypress
        #else
        case CC_OLED_DARK:
            return false;
        case CC_OLED_LGHT:
            return false;
        #endif
        default:
            return true;  // Process all other keycodes normally
    }
}

/* Combos */
#ifdef COMBO_ENABLE
const uint16_t PROGMEM next_layer_combo[] = {CC_FUNC, KC_VOLU, COMBO_END};
const uint16_t PROGMEM prev_layer_combo[] = {CC_FUNC, KC_VOLD, COMBO_END};
const uint16_t PROGMEM reboot_combo[] = {CC_FUNC, KC_MUTE, COMBO_END};

combo_t key_combos[] = {
    COMBO(next_layer_combo, CC_NEXT_LAYER),
    COMBO(prev_layer_combo, CC_PREV_LAYER),
    COMBO(reboot_combo, QK_REBOOT),
};
#endif

/* Encoder function */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MEDIA_CONTROL] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_NUMPAD] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_KB_FN] = {ENCODER_CCW_CW(CC_PREV_LAYER, CC_NEXT_LAYER)},
    [_PARALYZED] = {ENCODER_CCW_CW(KC_NO, KC_NO)},
};
#endif

/* OLED */
#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (cc_func_pressed) {
        char brightness_buf[4];
        oled_set_cursor(1, 0);
        oled_write_P(PSTR("Brightness: "), false);
        oled_write_ln_P(PSTR(itoa(oled_get_brightness(), brightness_buf, 10)), false);
    } else {
        oled_set_cursor(0, 0);
        for (int i = oled_max_chars(); i > 0; i--) {
            oled_write_P(PSTR(" "), false);
        }
    }

    oled_set_cursor(1, 4);
    oled_write_P(PSTR("Layer: "), false);

    // Layer status
    switch (current_layer) {
        case _MEDIA_CONTROL:
            oled_write_P(PSTR("Media\n"), cc_func_pressed);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Numpad\n"), cc_func_pressed);
            break;
        case _KB_FN:
            oled_write_P(PSTR("Func\n"), cc_func_pressed);
            break;
        case _PARALYZED:
            oled_write_P(PSTR("Paralyzed\n"), cc_func_pressed);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), cc_func_pressed);
    }

    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    render_logo();
    oled_set_cursor(0, 3);
    oled_write_ln_P(PSTR("Rebooting...\n"), false);
    oled_write_ln_P(PSTR("Hold fn for DFU."), false);
    oled_write_ln_P(PSTR("Blue LED will blink\nif is in DFU"), false);
    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    writePinLow(GP25);
    return false;
}
#endif
