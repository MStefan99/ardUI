//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ARDUI_H
#define ARDUI_ARDUI_H

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include "screen.h"
#include "view.h"
#include "textView.h"
#include "llpi.h"


void ardUiSetupRoutine();  // User "setup()" function will be replaced by this custom function
void ardUiLoopRoutine();  // User "loop()" function will be replaced by this custom function
void ardUiLoopCaller(void*);  // User loop caller used by FreeRTOS


class ardUI {
public:
    static ardUI &getInstance();

    template<class ScreenClass>
    static void show();

    explicit ardUI(ardUI const &) = delete;

    void operator=(ardUI const &) = delete;

private:
    const uint16_t screenHeight {100};
    const uint16_t screenWidth {100};
    screen *currentScreen {nullptr};

    ardUI();
    static void ardUiTask(void*);
};


template<class ScreenClass>
void ardUI::show() {
    auto* screen = new ScreenClass();
    getInstance().currentScreen = screen;
}


#endif //ARDUI_ARDUI_H
