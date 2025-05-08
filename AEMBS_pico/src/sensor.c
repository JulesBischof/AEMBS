/*
 * Copyright (c) 2023-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "sensor.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuSHT31.h"
#include "McuSystemView.h"
#include "McuLog.h"
#include "task.h"

static TaskHandle_t _sensorTaskHandle = NULL;
static QueueHandle_t _eventQueue = NULL;
static SemaphoreHandle_t _sensorDataMutex = NULL;
static float temperature, humidity; /* note: values need to be from the exact same measurement! */

//SW06! 
void Sensor_GetValues(float *pTemperature, float *pHumidity)
{
  if(xSemaphoreTake(_sensorDataMutex, portMAX_DELAY) != pdTRUE)
  {
    McuLog_error("ERROR sensor.c Mutex take failed");
    return;
  }
  *pTemperature = temperature;
  *pHumidity = humidity;
  xSemaphoreGive(_sensorDataMutex);
  return;
}

static void _sensorTask(void *pv)
{
  /* --- init vars --- */
  temperature = 0;
  humidity = 0;

  TickType_t lastWakeTime = xTaskGetTickCount();

  /* --- Task loop --- */
  while (1)
  {
    uint8_t sht31RetVal = 0;

    if(xSemaphoreTake(_sensorDataMutex, portMAX_DELAY) != pdTRUE)
    {
      McuLog_error("ERROR sensor.c Mutex take failed");
      return;
    }
    sht31RetVal = McuSHT31_ReadTempHum(&temperature, &humidity);
    xSemaphoreGive(_sensorDataMutex);

    /* check retVal */
    if (sht31RetVal != ERR_OK)
    {
      /* ERROR */
      McuLog_error("ERROR sht31RetVal");
    }

#if PL_READ_SENSORDATA_USING_QUEUES
    SensorData_t sensorData = {
        .temperature = temperature,
        .humidity = humidity};
      if (_eventQueue != NULL)
      {
        if (xQueueSendToBack(_eventQueue, &sensorData, portMAX_DELAY) != pdPASS)
        {
          McuLog_error("ERROR sensor.c Queue send failed");
          while(1){}
        }
        McuSystemView_Print("Values written to SensorQueue");
      }
      else
      {
        McuLog_error("ERROR sensor.c EventQueue = NULL");
      }
    vTaskSuspend(NULL); // suspend task until it gets retriggered
#else
    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(2000));
#endif

  }
}

void Sensor_TriggerMeasurment(void)
{
  /* fn might not be called from sensortask itself - thats why we don't want to use NULL-arg */
  vTaskResume(_sensorTaskHandle);
}

void Sensor_RegisterEventQueue(QueueHandle_t queue)
{
  if(queue != NULL)
  {
    _eventQueue = queue;
  }
  else 
  {
    McuLog_error("ERROR sensor.c Register EventQueue = NULL");
    while (1)
    { /* ERROR */
    }
  }
}

void Sensor_Init(void)
{
  _sensorDataMutex = xSemaphoreCreateMutex();

  if (_sensorDataMutex == NULL)
  {
    McuLog_error("ERROR sensor.c Mutex = NULL");
    while (1)
    { /* ERROR */
    }
  }

  BaseType_t checkVal = pdFALSE;
  checkVal = xTaskCreate(_sensorTask,
                         "sensorTask",
                         1024 / sizeof(StackType_t),
                         NULL,
                         tskIDLE_PRIORITY + 2,
                         &_sensorTaskHandle);

  if (checkVal != pdTRUE)
  {
    McuLog_error("ERROR sensor.c TaskHandle creation failed\n");
    while (1)
    {
      /* ERROR ?? */
    }
  }
}

void Sensor_Deinit(void)
{
  vTaskDelete(_sensorTaskHandle);
  _sensorTaskHandle = NULL;

  vSemaphoreDelete(_sensorDataMutex);
  _sensorDataMutex = NULL;

#if PL_READ_SENSORDATA_USING_QUEUES
  vQueueDelete(_eventQueue);
  _eventQueue = NULL;
#endif
}