#ifndef __SW5_H_
#define __SW5_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#include "McuRTOS.h"
#include "McuLED.h"

void sw5_loop(void);

void sw5_run(void);

/* ---- static members ---- */
static TaskHandle_t taskHandle;
static McuLED_Handle_t led;

#endif /* __SW4_H_ */