/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee switch driver example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#pragma once

#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* user should configure which I/O port as toggle switch input, default is GPIO9 */
#define GPIO_INPUT_IO_TOGGLE_SWITCH  GPIO_NUM_9

/* config button level depends on the pull up/down setting
   push button level is on level = 1 when pull-down enable
   push button level is on level = 0 when pull-up enable
*/
#define GPIO_INPUT_LEVEL_ON     0

#define ESP_INTR_FLAG_DEFAULT   0

#define PAIR_SIZE(TYPE_STR_PAIR) (sizeof(TYPE_STR_PAIR) / sizeof(TYPE_STR_PAIR[0]))

typedef enum {
    SWITCH_IDLE,
    SWITCH_PRESS_ARMED,
    SWITCH_PRESS_DETECTED,
    SWITCH_PRESSED,
    SWITCH_RELEASE_DETECTED,
} switch_state_t;

typedef enum {
    SWITCH_ON_CONTROL,
    SWITCH_OFF_CONTROL,
    SWITCH_ONOFF_TOGGLE_CONTROL,
    SWITCH_LEVEL_UP_CONTROL,
    SWITCH_LEVEL_DOWN_CONTROL,
    SWITCH_LEVEL_CYCLE_CONTROL,
    SWITCH_COLOR_CONTROL,
} switch_func_t;

typedef struct {
    uint32_t pin;
    switch_func_t func;
} switch_func_pair_t;

typedef void (*esp_switch_callback_t)(switch_func_pair_t *param);

/**
 * @brief init function for switch and callback setup
 *
 * @param button_func_pair      pointer of the button pair.
 * @param button_num            number of button pair.
 * @param cb                    callback pointer.
 */
bool switch_driver_init(switch_func_pair_t *button_func_pair, uint8_t button_num, esp_switch_callback_t cb);

#ifdef __cplusplus
} // extern "C"
#endif
