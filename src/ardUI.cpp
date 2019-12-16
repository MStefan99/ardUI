//
// Created by MStefan99 on 16.12.19.
//

#include <ardUI.h>


ardUI::ardUI() :
        screenHeight(ardUiDisplayGetHeight()),
        screenWidth(ardUiDisplayGetWidth()),
        currentScreen(nullptr) {
    xTaskCreate(ardUiTask, "UI task", 100, nullptr, tskIDLE_PRIORITY, nullptr);
}


ardUI &ardUI::getInstance() {
    static ardUI instance;
    return instance;
}


void ardUI::ardUiTask(void *) {
    while (true) {
        // Check for events and call necessary callbacks here
    }
}