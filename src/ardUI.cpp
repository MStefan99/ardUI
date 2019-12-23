//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


#undef ardUI


#if FREERTOS_ENABLED

#undef setup
#undef loop
#undef delay


void ardUI::ardUiTask(void *) {
    while (true) {
        draw();
        checkForActions();
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
    delete currentScreen;
}


ardUI &ardUI::getInstance() {
    static ardUI instance;
    return instance;
}


screen* ardUI::getCurrentScreen() {
    return getInstance().currentScreen;
}


void ardUI::back() {
    auto s {getInstance().currentScreen};

    if (s) {
        if (getInstance().currentDialog) {
            getInstance().currentDialog = nullptr;
            s->resume();
        }

        if (getInstance().backStack.length() > 0) {
            s->pause();
            s->stop();
            s->destroy();
            delete s;

            s = getInstance().backStack.popLeft();
            getInstance().currentScreen = s;
            s->restart();
            s->start();
            s->resume();
        }
    }
}


void ardUI::showDialog(dialog *dialogToShow) {
    auto s {getInstance().currentScreen};

    if (s) {
        s->pause();
        getInstance().currentDialog = dialogToShow;
    }
}


void ardUI::checkForActions() {
    if (ardUiDisplayIsClicked()) {
        static uint16_t x, y;
        ardUiDisplayClickLocation(x, y);
        getInstance().getCurrentScreen()->getRootView()->forEach([](view* v) {
            if (v->coordsInside(x, y)) {
                if (v->onClick) {
                    v->onClick(v);
                }
            }
        });
    }
}


void ardUI::draw() {
    if (getInstance().currentDialog) {
        getInstance().currentDialog->draw();
    }

    if (getInstance().currentScreen) {
        getInstance().currentScreen->draw();
    }
}
