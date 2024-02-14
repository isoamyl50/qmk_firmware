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
// #define AUDIO_PIN GP15
// #define AUDIO_PWM_DRIVER PWMD7
// #define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
// #define AUDIO_INIT_DELAY

// #ifdef AUDIO_ENABLE
// #   define STARTUP_SONG SONG(S__NOTE(_G5))
// #endif

/* Hold Encoder button while plugging in to enter bootloader */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 3

/* Encoder pads */
#define ENCODERS_PAD_A { GP9 }
#define ENCODERS_PAD_B { GP8 }
#define ENCODER_RESOLUTION 4

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
