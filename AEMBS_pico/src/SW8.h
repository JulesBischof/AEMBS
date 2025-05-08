#ifndef __SW8_H__
#define __SW8_H__

#include "FreeRTOS.h"
#include "task.h"

#include "buttons.h"
#include "McuDebounce.h"

#include "McuRTOS.h"

#define EVENT_QUEUE_LENGTH (5)
#define EVENT_QUEUE_ITEM_SIZE (sizeof(Buttons_e))

#define SENSOR_QUEUE_LENGTH (5)
#define SENSOR_QUEUE_ITEM_SIZE (sizeof(SensorData_t))

//!< \brief app-entrypoint for SW08 for SW8 */
void sw8_entry(void);

//!< \brief button event Handler SW8-Labs */
void App_OnDebounceButtonEvent(Buttons_e button, McuDbnc_EventKinds kind);

#endif /* __SW8_H__ */