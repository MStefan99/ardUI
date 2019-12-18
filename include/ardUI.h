//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ARDUI_H
#define ARDUI_ARDUI_H

#include <Arduino.h>
#include "ardUI_config.h"

#if FREERTOS_ENABLED
#include <Arduino_FreeRTOS.h>
#include <task.h>

// Hiding standard Arduino functions for correct operation of FreeRTOS
void ardUiSetupRoutine();  // User "setup()" function will be replaced by this custom function
void ardUiLoopRoutine();  // User "loop()" function will be replaced by this custom function
void ardUiLoopCaller(void*);  // User loop caller used by FreeRTOS

#define setup() ardUiSetupRoutine()  // Replacing default setup with custom
#define loop() ardUiLoopRoutine()  // Replacing default loop with custom

#endif


#include "screen.h"
#include "view.h"
#include "view_group.h"
#include "text_view.h"
#include "llpi.h"


class ardUI {
public:
    static ardUI &getInstance();

    template<class ScreenClass>
    static void show();

    explicit ardUI(ardUI const &) = delete;

    void operator=(ardUI const &) = delete;

private:
    ardUI();
    ~ardUI();

    const uint16_t screenHeight {ardUiDisplayGetHeight()};
    const uint16_t screenWidth {ardUiDisplayGetWidth()};
    screen* currentScreen {nullptr};
    list<screen*> backStack {};

    static void ardUiTask(void*);
};


template<class ScreenClass>
void ardUI::show() {
    if (getInstance().currentScreen) {
        getInstance().currentScreen->onPause();
        getInstance().backStack.prepend(getInstance().currentScreen);
        Serial.println("Screen appended to the stack");

        if (getInstance().backStack.length() > BACK_STACK_DEPTH) {
            Serial.println("Max stack depth reached, destroying last screen");
            auto lastScreen = getInstance().backStack.pop();
            lastScreen->onStop();
            lastScreen->onDestroy();
            delete lastScreen;
        }
    }
    auto* screen = new ScreenClass();
    getInstance().currentScreen = screen;

    getInstance().currentScreen->onCreate();
    getInstance().currentScreen->onStart();
    getInstance().currentScreen->onResume();
}


#endif //ARDUI_ARDUI_H
