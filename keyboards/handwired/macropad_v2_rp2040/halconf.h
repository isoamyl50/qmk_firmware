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

/* Enable PWM */
// #define HAL_USE_PWM                 TRUE
// #define HAL_USE_PAL                 TRUE

/* Enable I2C */
#define HAL_USE_I2C                 TRUE

#include_next <halconf.h>
