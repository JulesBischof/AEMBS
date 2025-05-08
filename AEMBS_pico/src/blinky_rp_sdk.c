/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "blinky_rp_sdk.h"
#include "hardware/gpio.h"

#include "platform.h"


void blinky_sdk_rp(void) {
    const unsigned int LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    
    gpio_set_dir(LED_PIN, GPIO_OUT);
    for(;;) {
        gpio_put(LED_PIN, 0);
        McuWait_Waitms(100);
        gpio_put(LED_PIN, 1);
        McuWait_Waitms(500);
    }
}
