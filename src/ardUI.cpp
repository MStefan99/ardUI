//
// Created by MStefan99 on 16.12.19.
//

#include <ardUI.h>


ardUI::ardUI() :
        screenHeight(ardUiDisplayGetHeight()),
        screenWidth(ardUiDisplayGetWidth()),
        currentScreen(nullptr) {}


ardUI &ardUI::getInstance() {
    static ardUI instance;
    return instance;
}
