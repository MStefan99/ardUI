//
// Created by MStefan99 on 16.12.19.
//

#include <ardUI.h>


ardUI::ardUI(): screenHeight(ardUiDisplayGetHeight()), screenWidth(ardUiDisplayGetWidth()) {

}


ardUI &ardUI::getInstance() {
    static ardUI instance;
    return instance;
}


template <class ScreenClass>
void ardUI::show(ScreenClass c) {
    ScreenClass screen = new ScreenClass();
    getInstance().currentScreen = screen;
}


ardUI &ardUI::operator()() const {
    return getInstance();
}
