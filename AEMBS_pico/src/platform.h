/*
 * Copyright (c) 2023-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* SW01: Introcuction */
#define PL_CONFIG_USE_SDK_BLINKY            (1) /* implements an endless loop with RP2040 SDK */

/* SW02: Architecture */
#define PL_CONFIG_USE_SDK_BLINKY_MCULIB     (0 && PL_CONFIG_USE_SDK_BLINKY) /* replacing SDK blinky with McuLib version */

/* SW03: Development */
#define PL_CONFIG_USE_BM_LOOP               (0) /* bare metal loop with McuLib (leds, buttons, wait, CDC) */

/* SW04: Firmware */
#define PL_CONFIG_USE_BUTTONS               (0) /* adding button support */
#define PL_CONFIG_USE_BUTTONS_ISR           (0 && PL_CONFIG_USE_BUTTONS) /* using buttons with interrupts */

/* SW05: RTOS */
#define PL_CONFIG_USE_BLINKY_TASK           (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* blinky task created from app task, printing button messages */

/* SW06: Kernel */
#define PL_CONFIG_USE_SENSOR_TASK           (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* sensor values printed with 1 Hz */
#define PL_CONFIG_USE_SYSTEM_VIEW_LOG       (0 && configUSE_SEGGER_SYSTEM_VIEWER_HOOKS) /* logging SystemView messages */

/* SW07: Synchronization */
#define PL_CONFIG_USE_FROM_ISR_YIELD        (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* Yielding in ISR or no yield*/

/* SW08: Messages */
// PRE: enabled configUSE_TIMERS
#define PL_CONFIG_USE_DEBOUNCE              (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* debouncing the buttins with timer */

/* SW09: Parallel Processes */
#define PL_CONFIG_USE_SHELL                 (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* using command line shell user interface */
#define PL_CONFIG_USE_CDC_LOCK              (0 && PL_CONFIG_USE_SHELL) /* locking/unlocking the USB CDC channel */

/* SW10: User Interface */
#define PL_CONFIG_USE_OLED_LCD              (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* Using OLED display for game */
#define PL_CONFIG_USE_GAME                  (0 && PL_CONFIG_USE_OLED_LCD)   /* game with MVC architecture */

/* SW11: Graphic */
/* \todo TBD */

/* SW12: Notification */
/* \todo TBD */

/* SW13: Game & Closure */
/* \todo TBD */

/*!
 * \brief de-initializes the platform
 */
void PL_Deinit(void);

/*!
 * \brief initializes the platform
 */
void PL_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* PLATFORM_H_ */
