#include "SW5.h"

#include "McuShellCdcDevice.h"

#include "platform.h"
#include "buttons.h"
#include "McuWait.h"

#include "buttons_config.h"

#include "McuSystemView.h"

void sw5_loop(void)
{
    /* --- init module ---  */
    sw5_init();

    /* ---- init Task ----- */
    if (xTaskCreate(
            sw5_run,                   /* pointer to the task */
            " sw5 main ",              /* task name for kernel awareness debugging */
            600 / sizeof(StackType_t), /* task stack size */
            (void *)NULL,              /* optional task startup argument */
            tskIDLE_PRIORITY + 2,      /* initial priority */
            &taskHandle                /* optional task handle to create */
            ) != pdPASS)
    {
        for (;;)
        {
        } /* error ! probably out of memory */
    }

    /* ---- start Scheduler ---- */
    vTaskStartScheduler();
    // never reched
    while (1)
    {
    };

#if PL_CONFIG_USE_BUTTONS_ISR == 0
    // use polling
    sw5_run();

#endif
#if PL_CONFIG_USE_BUTTONS_ISR == 1
    // Aufgabe ISR
#endif
}

void sw5_init(void)
{
    /* --- init submodules --- */
    Buttons_Init();
    McuShellCdcDevice_Init();
    McuRTOS_Init();

    /* --- init LED --- */
    // create default config LED
    McuLED_Config_t configLED;

    McuLED_GetDefaultConfig(&configLED);
    configLED.isOnInit = false;
    configLED.hw.pin = PICO_DEFAULT_LED_PIN;
    configLED.isOnInit = false;
    configLED.isLowActive = false;

    // create LED-instance
    led = McuLED_InitLed(&configLED);
}
// App_OnISRButtonPressed

void sw5_run(void)
{

    McuShellCdcDevice_WriteStr("Hello World from SW05! \r\n");
    McuShellCdcDevice_Flush();

    for (;;)
    {
        McuLED_Toggle(led);

        int32_t buttonFlags = Buttons_GetButtons();

        if (buttonFlags)
        {
            if (buttonFlags & BUTTONS_BIT_NAV_CENTER)
            {
                McuShellCdcDevice_WriteStr("CENTER! \r\n");
            }
            if (buttonFlags & BUTTONS_BIT_NAV_UP)
            {
                McuShellCdcDevice_WriteStr("UP! \r\n");
            }
            if (buttonFlags & BUTTONS_BIT_NAV_DOWN)
            {
                McuShellCdcDevice_WriteStr("DOWN! \r\n");
            }
            if (buttonFlags & BUTTONS_BIT_NAV_LEFT)
            {
                McuShellCdcDevice_WriteStr("LEFT! \r\n");
            }
            if (buttonFlags & BUTTONS_BIT_NAV_RIGHT)
            {
                McuShellCdcDevice_WriteStr("RIGHT! \r\n");
            }
            McuShellCdcDevice_Flush();
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}