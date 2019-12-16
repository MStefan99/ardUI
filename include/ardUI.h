//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ARDUI_H
#define ARDUI_ARDUI_H

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include "screen.h"
#include "view.h"
#include "llpi.h"


class ardUI {
public:
    static ardUI &getInstance();

    template<class ScreenClass>
    static void show();

    explicit ardUI(ardUI const &) = delete;

    void operator=(ardUI const &) = delete;

private:
    const uint16_t screenHeight;
    const uint16_t screenWidth;
    screen *currentScreen;

    ardUI();
};


template<class ScreenClass>
void ardUI::show() {
    auto* screen = new ScreenClass();
    getInstance().currentScreen = screen;
}


#endif //ARDUI_ARDUI_H
