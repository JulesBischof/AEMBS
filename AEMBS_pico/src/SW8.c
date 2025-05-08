#include "SW8.h"

#include "debounce.h"
#include "buttons.h"
#include "McuLog.h"
#include "sensor.h"

static QueueHandle_t _eventQueue;
static QueueHandle_t _sensorQueue;

void _sw8_task(void *pv)
{
    Buttons_e button = 0;
    SensorData_t sensorData = {0};

    while (1)
    {
        if(xQueueReceive(_eventQueue, &button, portMAX_DELAY) != pdPASS)
        {
            McuLog_error("Error receiving from event queue");
            continue; // retry
        }
        McuLog_info("Button event: %d", button);

        Sensor_TriggerMeasurment();
        if(xQueueReceive(_sensorQueue, &sensorData, pdMS_TO_TICKS(20)) != pdPASS)
        {
            McuLog_error("Timeout sensor queue");
            continue; // retry
        }
        McuLog_info("SensorData: temp: %f°C hum:%f perc", sensorData.temperature, sensorData.humidity);
    }
}

static void _init(void)
{
    _eventQueue = xQueueCreate(EVENT_QUEUE_LENGTH, EVENT_QUEUE_ITEM_SIZE);
    if (_eventQueue == NULL)
    {
        McuLog_error("Error creating event queue");
        while (1)
        {/* ERROR */
        }
    }
    vQueueAddToRegistry(_eventQueue, "sw8_event_queue");

    _sensorQueue = xQueueCreate(SENSOR_QUEUE_LENGTH, SENSOR_QUEUE_ITEM_SIZE);
    if (_sensorQueue == NULL)
    {
        McuLog_error("Error creating sensor queue");
        while (1)
        {/* ERROR */
        }
    }
    vQueueAddToRegistry(_sensorQueue, "sw8_sensor_queue");

    // subscribe to sensor event queue - trigger first measurment so queue is not empty
    Sensor_RegisterEventQueue(_sensorQueue);
    Sensor_TriggerMeasurment();
}

void App_OnDebounceButtonEvent(Buttons_e button, McuDbnc_EventKinds kind)
{
    if (kind == MCUDBNC_EVENT_PRESSED)
        if (xQueueSendToBack(_eventQueue, &button, 0) != pdPASS)
        {
            McuLog_error("Error adding to event queue");
        }
}

void sw8_entry(void)
{
    Buttons_Init();
    Debounce_Init();
    Sensor_Init();

    if (xTaskCreate(_sw8_task,
                    "sw8_task",
                    2 * 1024 / sizeof(StackType_t),
                    NULL,
                    tskIDLE_PRIORITY + 1,
                    NULL) != pdTRUE)
    {
        for (;;)
        {
            McuLog_error("Error creating task sw8_task");
        } /* ERROR */
    }

    _init();

    vTaskStartScheduler(); /* start scheduler */
    /* never reached */
    return;
}