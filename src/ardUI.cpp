//
// Created by MStefan99 on 16.12.19.
//

#include <ardUI.h>


ardUI::ardUI() :
        screenHeight(ardUiDisplayGetHeight()),
        screenWidth(ardUiDisplayGetWidth()) {
    xTaskCreate(ardUiTask, "UI task", 100,
            nullptr, tskIDLE_PRIORITY, nullptr);
}


ardUI &ardUI::getInstance() {
    static ardUI instance;
    return instance;
}


void ardUI::ardUiTask(void *) {
    while (true) {
        // TODO: Check for events and call necessary callbacks here
    }
}


void setup() {  // Default setup function will be used to create FreeRTOS loop task
    ardUiSetupRoutine();  // Calling user setup routine
    xTaskCreate(ardUiLoopCaller, "Main loop", 500,
                nullptr, tskIDLE_PRIORITY + 3, nullptr); // Creating loop task
}


void loop() {}  // Default loop should be left empty


void ardUiLoopCaller(void*) {  // User loop caller used by FreeRTOS
    while (true) {
        ardUiLoopRoutine();  // Calling user loop routine in an infinite loop
    }
}
