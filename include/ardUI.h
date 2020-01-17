//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ARDUI_H
#define ARDUI_ARDUI_H

#include <Arduino.h>
#include "ardUI_config.h"
#include "llpi.h"

#include "activity.h"
#include "dialog.h"

#include "view.h"
#include "text_view.h"
#include "button_view.h"

#include "view_group.h"
#include "linear_layout.h"

// Hiding standard Arduino functions for correct operation of ardUI
void ardUiUserSetup();  // User "setup()" function will be replaced by this custom function
void ardUiUserLoop();  // User "loop()" function will be replaced by this custom function

#define setup() ardUiUserSetup()
#define loop() ardUiUserLoop()


class ardUI {
public:
    explicit ardUI(ardUI const &) = delete;

    static ardUI& getInstance();
    static activity& getCurrentScreen();

    template<class ScreenClass>
    static void showScreen();
    static void showDialog(dialog& dialogToShow);
    static void back();

    static void callActivityOnCreate(activity* activity);
    static void callActivityOnStart(activity* activity);
    static void callActivityOnRestart(activity* activity);
    static void callActivityOnResume(activity* activity);
    static void callActivityOnPause(activity* activity);
    static void callActivityOnStop(activity* activity);
    static void callActivityOnDestroy(activity* activity);

    void operator=(ardUI const &) = delete;

    static void checkForActions();
    static void draw();

private:
    ardUI() = default;
    ~ardUI();


    const uint16_t screenHeight {ardUiDisplayGetHeight()};
    const uint16_t screenWidth {ardUiDisplayGetWidth()};
    activity* currentActivity {nullptr};
    dialog* currentDialog {nullptr};
    list<activity*> backStack {};
};


template<class ScreenClass>
void ardUI::showScreen() {
    auto s {getInstance().currentActivity};
    if (s) {
        callActivityOnStop(s);
        getInstance().backStack.pushFront(s);
        Serial.println("Screen appended to the stack");

        if (getInstance().backStack.length() > BACK_STACK_DEPTH) {
            Serial.println("Max stack depth reached, destroying last activity");
            auto lastScreen {getInstance().backStack.popBack()};
            callActivityOnDestroy(lastScreen);
            delete lastScreen;
        }
    }
    s = new ScreenClass();
    getInstance().currentActivity = s;

    callActivityOnResume(s);
}


#define ardUI() ardUI::getInstance()  // Instantiates ardUI from "ardUI()" call (discouraged)

#endif //ARDUI_ARDUI_H
