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


#include "llpi.h"

#include "screen.h"
#include "dialog.h"

#include "view.h"
#include "text_view.h"
#include "button_view.h"

#include "view_group.h"
#include "linear_layout.h"


class ardUI {
public:
    explicit ardUI(ardUI const &) = delete;

    static ardUI &getInstance();
    static screen* getCurrentScreen();

    template<class ScreenClass>
    static void showScreen();
    static void showDialog(dialog *dialogToShow);
    static void back();

    void operator=(ardUI const &) = delete;

private:
    ardUI();
    ~ardUI();

    const uint16_t screenHeight {ardUiDisplayGetHeight()};
    const uint16_t screenWidth {ardUiDisplayGetWidth()};
    screen* currentScreen {nullptr};
    dialog* currentDialog {nullptr};
    list<screen*> backStack {};

    static void ardUiTask(void*);
    static void checkForActions();
    static void draw();
};


template<class ScreenClass>
void ardUI::showScreen() {
    auto s {getInstance().currentScreen};
    if (s) {
        s->pause();
        s->stop();
        getInstance().backStack.prepend(s);
        Serial.println("Screen appended to the stack");

        if (getInstance().backStack.length() > BACK_STACK_DEPTH) {
            Serial.println("Max stack depth reached, destroying last screen");
            auto lastScreen = getInstance().backStack.pop();
            lastScreen->destroy();
            delete lastScreen;
        }
    }
    s = new ScreenClass();
    getInstance().currentScreen = s;

    s->create();
    s->start();
    s->resume();
}


#define ardUI() ardUI::getInstance()  // Instantiates ardUI from "ardUI()" call (discouraged)

#endif //ARDUI_ARDUI_H
