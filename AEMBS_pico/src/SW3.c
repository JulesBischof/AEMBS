#include "SW3.h"

#include "McuShellCdcDevice.h"

#include "McuWait.h"
#include "McuLED.h"

void sw3_loop(void)
{
    McuShellCdcDevice_WriteStr("Hello World from SW03! \r\n");
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

        if(ticks == 100)
        {
            McuLED_Toggle(led);
            ticks = 0;
            McuShellCdcDevice_WriteStr("Ticks reached! \r\n");
        }
        
        McuWait_Waitms(McuShellCdcDevice_CONFIG_PROCESS_WAIT_TIME_MS);
        McuShellCdcDevice_Process();
    }
}