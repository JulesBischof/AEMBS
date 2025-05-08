#include "SW6.h"

#include "sensor.h"
#include "McuLog.h"
#include "FreeRTOS.h"
#include "task.h"

static void sw6_TaskLoop(void* pvParam)
{
    float temperature = 0;
    float humidity = 0;

    TickType_t lastWakeTime = xTaskGetTickCount();

    while (1)
    {
        Sensor_GetValues(&temperature, &humidity);
        McuLog_info(" t: %f C , h:% f% %", temperature, humidity);

        // vTaskDelay(pdMS_TO_TICKS(5000));
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(5000));
    }
}

void sw6_loop(void)
{
    BaseType_t checkVal = pdFALSE;
    Sensor_Init();

    checkVal = xTaskCreate(sw6_TaskLoop,
                           "SW6 Task",
                           1024 / sizeof(StackType_t),
                           NULL,
                           tskIDLE_PRIORITY + 1,
                           NULL);

    if (checkVal != pdTRUE)
    {
        McuLog_error("SW6 TASK = pdFALSE\n");
        while (1)
        {
            /* ERROR */
        }
    }

    vTaskStartScheduler();
}