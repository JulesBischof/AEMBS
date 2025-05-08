#include "sw5_quiz.h"

#include "leds.h"

/* ---- static members ----*/
static TaskHandle_t taskHandle;

/* ---- getters for static members ---- */
TaskHandle_t getTaskHandle() { return taskHandle; }

/* ---- implementation ---- */

/// @brief running Task Loop, wich toggles LED on and off again
/// @param pv void ptr - containing a LED Handle
static void _sw5_led_Task(void *pv)
{
    Leds_Init();
    LEDS_Leds_e led = (LEDS_Leds_e)pv;
    TickType_t xLastWakeTime;

    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();
        Leds_Neg(led);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
    }
}

/// @brief Initializes Task as well as used peripherals
void run_sw5_led_Task()
{
    void *led1 = (void *)LEDS_RED;
    void *led2 = (void *)LEDS_GREEN;
    void *led3 = (void *)LEDS_BLUE;

    BaseType_t retVal1 = xTaskCreate(
        _sw5_led_Task,
        "sw5_led_Task_1",
        128 / sizeof(StackType_t),
        led1,
        tskIDLE_PRIORITY + 1,
        NULL);

    BaseType_t retVal2 = xTaskCreate(
        _sw5_led_Task,
        "sw5_led_Task_1",
        128 / sizeof(StackType_t),
        led2,
        tskIDLE_PRIORITY + 1,
        NULL);

    BaseType_t retVal3 = xTaskCreate(
        _sw5_led_Task,
        "sw5_led_Task_1",
        128 / sizeof(StackType_t),
        led3,
        tskIDLE_PRIORITY + 1,
        NULL);

    if (retVal1 != pdTRUE || retVal2 != pdTRUE || retVal3 != pdTRUE)
    {
        while (1)
        { /* ERROR */
        }
    }

    vTaskStartScheduler();

    return;
}