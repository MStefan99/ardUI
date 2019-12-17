//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_ARDUI_SETUP_H
#define ARDUI_ARDUI_SETUP_H

#include "ardUI.h"
#include <Arduino.h>

// Hiding standard Arduino functions for correct operation of FreeRTOS
#define setup() ardUiSetupRoutine()  // Replacing default setup with custom
#define loop() ardUiLoopRoutine()  // Replacing default loop with custom
#define delay(milliSecondsToWait) vTaskDelay(milliSecondsToWait / 15)  // Replacing default delay with FreeRTOS task delay

#endif //ARDUI_ARDUI_SETUP_H
