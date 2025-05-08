/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "cdcLock.h"
#include "McuRTOS.h"

#include "McuLog.h"

static SemaphoreHandle_t mutex = NULL; /* Mutex to protect access to CDC USB bus */

void CdcLock_Take(void) {
    if(xSemaphoreTakeRecursive(mutex, portMAX_DELAY) != pdPASS)
    {
        McuLog_error("CdcLock failed!\n");
    };
}

void CdcLock_Give(void) {
    xSemaphoreGiveRecursive(mutex);
}

void CdcLock_Deinit(void) {
    vSemaphoreDelete(mutex);
    mutex = NULL;
    McuLog_info("cdc log mutex deletd\n");
}

void CdcLock_Init(void) {
    mutex = xSemaphoreCreateRecursiveMutex();
    if(mutex == NULL)
    {
        McuLog_error("creating mutex in cdc lock failed\n");
        for (;;)
            ;
    }
    vQueueAddToRegistry(mutex, "cdc lock queue");
}

