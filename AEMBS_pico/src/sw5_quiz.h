#ifndef __SW5_QUIZ
#define __SW5_QUIZ

#include "FreeRTOS.h"
#include "task.h"

void run_sw5_led_Task();

TaskHandle_t getTaskHandle();

#endif