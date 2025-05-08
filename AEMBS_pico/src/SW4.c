#include "SW4.h"

#include "McuShellCdcDevice.h"

#include "platform.h"
#include "McuLED.h"
#include "buttons.h"
#include "McuWait.h"

#include "buttons_config.h"

void sw4_loop(void)
{
#if PL_CONFIG_USE_BUTTONS_ISR == 0
    // use polling
    sw4_UsePolling();

#endif
#if PL_CONFIG_USE_BUTTONS_ISR == 1
    // Aufgabe ISR
#endif
}

void sw4_UsePolling(void)
{
    /* --- init submodules --- */
    Buttons_Init();
    McuShellCdcDevice_Init();

    McuShellCdcDevice_WriteStr("Hello World from SW04! \r\n");
    McuShellCdcDevice_Flush();

    int ticks = 0;

    // create default config LED
    McuLED_Config_t configLED;

    McuLED_GetDefaultConfig(&configLED);
    configLED.isOnInit = false;
    configLED.hw.pin = PICO_DEFAULT_LED_PIN;
    configLED.isOnInit = false;
    configLED.isLowActive = false;

    // create LED-instance
    McuLED_Handle_t led;
    led = McuLED_InitLed(&configLED);

    for (;;)
    {
        ticks++;

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

        if (ticks == 100)
        {
            McuLED_Toggle(led);
            ticks = 0;
            McuShellCdcDevice_WriteStr("Ticks reached! \r\n");
            McuShellCdcDevice_Flush();
        }

        McuWait_Waitms(McuShellCdcDevice_CONFIG_PROCESS_WAIT_TIME_MS);
        McuShellCdcDevice_Process();
        
    }
}