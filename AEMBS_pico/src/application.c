/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "application.h"

#include "blinky_rp_sdk.h"
#include "shell.h"
#include "cdcLock.h"
#include "McuLog.h"
#include "McuShellCdcDevice.h"

#include "game.h"
#include "sensor.h"
#include "leds.h"
#include "buttons.h"
#include "debounce.h"

#include "SW2.h"
#include "SW3.h"
#include "SW4.h"
#include "sw5_quiz.h"
#include "SW6.h"
#include "SW7.h"
#include "SW8.h"

/**
 * @brief prints a cat on the Serial command window. neccessary for Quiz SW10
 */
static void _printCat(void)
{
  const char *cat =
      "|\\__/,|   (`\\  \n"
      "|_ _  |.--.) )   \n"
      "( T   )      /   \n"
      "(((^_(((/(((_/   \n";

  CdcLock_Take();
  McuShellCdcDevice_WriteStr(cat);
  McuShellCdcDevice_Flush();
  CdcLock_Give();
}

/**
 * @brief applicationTask SW10
 */
static void _appTask(void *pv)
{
  // get SensorData
  float temperature = 0;
  float humidity = 0;
  vTaskDelay(100); // wait some ms until sensorData is ready to read
  Sensor_GetValues(&temperature, &humidity);
  Sensor_Deinit(); // kill SensorTask

  // cast to int value
  int seed = (int)humidity;

  // set seed
  Game_OnNewRandomSeed(seed);

  // give cdc some time to connect
  vTaskDelay(2000);
  _printCat();

  vTaskSuspend(NULL); // suspend Task

  CdcLock_Take();
  McuLog_error("ERROR! _appTask RESUMED \r\n");
  CdcLock_Give();

  for (;;)
    ; /* fatal error - stop here */
}

void App_Run(void)
{
  PL_Init(); /* initialize platform and drivers */

  Leds_Init();
  Buttons_Init();
  Debounce_Init();

  Shell_Init();
  Game_Init();
  CdcLock_Init();
  Sensor_Init();

// SW1
#if PL_CONFIG_USE_SDK_BLINKY
  blinky_sdk_rp();
#endif

// SW2
#if PL_CONFIG_USE_SDK_BLINKY_MCULIB
  sw2_blinky();
#endif

// SW3
#if PL_CONFIG_USE_BM_LOOP
  sw3_loop();
#endif

// SW4
#if PL_CONFIG_USE_BUTTONS
  sw4_loop();
#endif

// SW5
#if PL_CONFIG_USE_BLINKY_TASK
  sw5_loop();
#endif
#if SW05_BLINKYTASK_QUIZ
  run_sw5_led_Task();
#endif

// SW6
#if PL_CONFIG_USE_SENSOR_TASK // PL_CONFIG_USE_SYSTEM_VIEW_LOG
  sw6_loop();
#endif

// SW7
#if PL_CONFIG_USE_FROM_ISR_YIELD // PL_CONFIG_USE_SYSTEM_VIEW_LOG
  sw7_entry();
#endif

// SW8
#if PL_RUN_SW8_SUBMODULE
  sw8_entry();
#endif

#if PL_CONFIG_USE_GAME // SW9 / SW10

  // create Task that generates seeds for the games random generator
  if (xTaskCreate(_appTask,
                  "_appTask",
                  10 * 1024 / sizeof(StackType_t),
                  NULL,
                  tskIDLE_PRIORITY + 1,
                  NULL) != pdPASS)
  {
    CdcLock_Take();
    McuShellCdcDevice_WriteStr("ERROR! _sensorReadTask creation FAILED\r\n");
    McuShellCdcDevice_Flush();
    CdcLock_Give();
    for (;;)
    { /* fatal - stop here */
    }
  }
#endif

  vTaskStartScheduler();
  PL_Deinit(); /* deinitialize the platform */
}