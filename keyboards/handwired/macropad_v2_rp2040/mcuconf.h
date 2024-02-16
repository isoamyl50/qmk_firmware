/* Copyright 2024 Hoang Nguyen (@isoamyl50)
 *
 * This file if part of the QMK Firmware
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

#include_next <mcuconf.h>

/* Enable PWM Driver 7 */
#ifdef AUDIO_ENABLE
    #undef RP_PWM_USE_PWM7
    #define RP_PWM_USE_PWM7 TRUE
#endif

/* Enable I2C */
#ifdef OLED_ENABLE
    #undef RP_I2C_USE_I2C0
    #define RP_I2C_USE_I2C0 TRUE

    #undef RP_I2C_USE_I2C1
    #define RP_I2C_USE_I2C1 TRUE
#endif
