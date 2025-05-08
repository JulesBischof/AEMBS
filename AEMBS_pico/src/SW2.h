#ifndef __SW2_H_
#define __SW2_H_

#include "McuLED.h"
#include "McuGPIO.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void initLed(void);
    void initGpio(void);
    void sw2_blinky(void);
    void sw2_task(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SW2_H_ */