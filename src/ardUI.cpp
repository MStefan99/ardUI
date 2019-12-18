//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


#if FREERTOS_ENABLED

#undef setup
#undef loop
#undef delay


void ardUI::ardUiTask(void *) {
    while (true) {
        //TODO: Check for events and call necessary callbacks here
    }
}


void setup() {  // Default setup function will be used to create FreeRTOS loop task
    ardUiSetupRoutine();  // Calling user setup routine
    xTaskCreate(ardUiLoopCaller, "Main loop", 500,
                nullptr, tskIDLE_PRIORITY + 3, nullptr); // Creating loop task
#define delay(milliSecondsToWait) vTaskDelay(milliSecondsToWait / 15)  // Replacing default delay with FreeRTOS task delay
}


void loop() {}  // Default loop should be left empty


void ardUiLoopCaller(void*) {  // User loop caller used by FreeRTOS
    while (true) {
        ardUiLoopRoutine();  // Calling user loop routine in an infinite loop
    }
}

#endif


ardUI::ardUI() {
#if FREERTOS_ENABLED
    xTaskCreate(ardUiTask, "UI task", 100,
            nullptr, tskIDLE_PRIORITY, nullptr);
#endif
}


ardUI::~ardUI() {
    for (auto s : backStack) {
        delete s;
    }
}


ardUI &ardUI::getInstance() {
    static ardUI instance;
    return instance;
}
