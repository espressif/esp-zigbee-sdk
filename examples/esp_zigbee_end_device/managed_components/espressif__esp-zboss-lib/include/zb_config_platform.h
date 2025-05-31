/*
 * Copyright (c) 2021 Espressif Systems (Shanghai) CO LTD
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Espressif Systems
 *    integrated circuit in a product or a software update for such product,
 *    must reproduce the above copyright notice, this list of conditions and
 *    the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * 4. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "sdkconfig.h"
#include "hal/gpio_types.h"
#include "hal/uart_types.h"
#include "driver/uart.h"
#include "esp_ieee802154_types.h"

#define ZB_ESP
#define ZB_CONFIG_ESP

#define ZB_LEDS_MASK
#define ZB_USE_BUTTONS
#define ZB_SOFT_SECURITY

#define MAC_TRANSPORT_USES_SELECT

#define ZB_LITTLE_ENDIAN
#define ZB_NEED_ALIGN

/* our MAC */
#define ZB_MANUAL_ACK
#define ZB_AUTO_ACK_TX
#define ZB_MAC_AUTO_ACK_RECV
#define ZB_MAC_RX_QUEUE_CAP 20
#define ZB_MAC_TIMESTAMP_IN_PKT
#define MAC_AUTO_DELAY_IN_MAC_GP_SEND

/* MAC Pending  Bit Matching */
#define ZB_MAC_PENDING_BIT_SOURCE_MATCHING
#define ZB_MAC_HARDWARE_PB_MATCHING

#define ZB_GPD_TX_OFFSET_US                                   \
  (ZB_MILLISECONDS_TO_USEC(ZB_GPD_RX_OFFSET_MS) -             \
   2 * ZB_MAC_A_UNIT_BACKOFF_PERIOD * ZB_SYMBOL_DURATION_USEC \
   - 900)

/* Default long poll interval */
uint32_t zb_get_default_long_poll_interval(void);
#define ESP_ZB_PIM_DEFAULT_LONG_POLL_INTERVAL  zb_get_default_long_poll_interval()
