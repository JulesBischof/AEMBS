/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "blinky_rp_sdk.h"
#include "hardware/gpio.h"

#include "platform.h"

static void delay(void) {
  for(volatile int i=0; i<3000000; i++) {
      __asm("nop");
  }
}


void threeShort(void) {
    for(int i = 0; i < 3; i++) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        delay();
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        delay();
    }
}

void threelong(void) {
    for(int i = 0; i < 3; i++) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        delay();
        delay();
        delay();
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        delay();
    }
}


void blinky_sdk_rp(void) {
    const unsigned int LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1)
    {
        threeShort();
        threelong();
        threeShort();

        delay();
        delay();
        delay();
    }


    /*
    for(;;) {
        gpio_put(LED_PIN, 0);
        delay();
        gpio_put(LED_PIN, 1);
        delay();
    }
    */
}