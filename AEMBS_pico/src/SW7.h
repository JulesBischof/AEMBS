#ifndef __SW7_H
#define __SW7_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


void sw7_entry(void);
TaskHandle_t getSw7TaskHandle(void);

#endif
