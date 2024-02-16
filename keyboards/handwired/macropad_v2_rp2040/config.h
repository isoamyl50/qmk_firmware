/* Copyright 2024 Hoang Nguyen (@isoamyl50)
 *
 * This file if part of the QMK Firmware
 *
 * The QMK Firmware program is free software: you can redistribute it and/or modify
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

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25 // Specify a optional status led by GPIO number which blinks when entering the bootloader

/*
 * Audio and Startup Beep
 *   refer RP2040 Datasheet for which PWM driver and channel to use with each pin
 */
#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(S__NOTE(_G5))
    #define AUDIO_PIN GP15
    #define AUDIO_PWM_DRIVER PWMD7
    #define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
    #define AUDIO_INIT_DELAY
#endif

/* Bootmagic: Hold Encoder button while plugging in to enter bootloader */
#ifdef BOOTMAGIC_LITE
    #define BOOTMAGIC_LITE_ROW 0
    #define BOOTMAGIC_LITE_COLUMN 2
#endif

/* Combos */
#ifdef COMBO_ENABLE
    #define COMBO_MUST_PRESS_IN_ORDER
    #define COMBO_TERM 65535
    #define COMBO_NO_TIMER
#endif

/* Encoder pads */
#ifdef ENCODER_ENABLE
    #define ENCODERS_PAD_A { GP9 }
    #define ENCODERS_PAD_B { GP8 }
    #define ENCODER_RESOLUTION 4
#endif

/* OLED Display */
#ifdef OLED_ENABLE
    #define OLED_DISPLAY_128X64
    #undef I2C_DRIVER
    #define I2C_DRIVER I2CD0
    #define OLED_DISPLAY_ADDRESS 0x3C
    #undef I2C1_SDA_PIN
    #define I2C1_SDA_PIN GP16
    #undef I2C1_SCL_PIN
    #define I2C1_SCL_PIN GP17
    #define OLED_BRIGHTNESS 127
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
