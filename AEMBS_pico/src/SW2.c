#include "SW2.h"

McuGPIO_Handle_t GpioPin;
McuGPIO_Config_t GpioConfig;

McuLED_Config_t configLED;
McuLED_Handle_t led;

void initLed(void)
{
    McuLED_GetDefaultConfig(&configLED);
    configLED.isOnInit = false;
    configLED.hw.pin = PICO_DEFAULT_LED_PIN;
    configLED.isOnInit = false;
    configLED.isLowActive = false;
    led = McuLED_InitLed(&configLED);
}

void initGpio(void)
{
    GpioConfig.isInput = true;
    GpioConfig.hw.pin = 11; // SW-Mid
    GpioConfig.hw.pull = McuGPIO_PULL_UP;

    GpioPin = McuGPIO_InitGPIO(&GpioConfig);

    if (GpioPin == NULL)
    {
        /* ERROR */
    }
}

void sw2_blinky(void)
{
    initGpio();
    initLed();

    for (;;)
    {
        McuLED_Off(led);
        McuWait_Waitms(100);
        McuLED_On(led);
        McuWait_Waitms(500);
    }
}

void sw2_task(void)
{
    initGpio();
    intLed();

    // loop
    while (1)
    {
        if (McuGPIO_IsLow(GpioPin))
            McuLED_On(led);
        else
            McuLED_Off(led);
    }
}