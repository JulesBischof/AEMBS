#include "SW7.h"

#include "buttons.h"
#include "McuLog.h"
#include "leds.h"

static void _sw7_task(void *pv)
{
    LEDS_Leds_e led = (LEDS_Leds_e)pv;
    for (;;)
    {
        Leds_Neg(led);
        McuLog_info("TASK Sw07 resumed from ISR! ");
        vTaskSuspend(NULL);
    }
}

static TaskHandle_t _taskHandle;
TaskHandle_t getSw7TaskHandle(void) { return _taskHandle; }

static void _sw7_startTask(void)
{
    Leds_Init();

    if (xTaskCreate(_sw7_task,
                    "SW7_TASK",
                    1024 / sizeof(StackType_t),
                    (void *)LEDS_BLUE,
                    tskIDLE_PRIORITY + 1,
                    &_taskHandle) != pdTRUE)
    {
        while (1)
        { /* ERROR */
        }
    }

    return;
}

void sw7_entry(void)
{
    Buttons_Init();
    _sw7_startTask();
    
    vTaskStartScheduler();

    /* never reached */

    return;
}