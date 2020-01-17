//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


#undef ardUI
#undef setup
#undef loop


void setup() {  // Default setup function will be used to initiate ardUI
    ardUiUserSetup();  // Calling user setup routine
}


void loop() {  // ardUI core functions will be added to the loop function
    ardUI::draw();
    ardUI::checkForActions();
    ardUiUserLoop();
}


ardUI::~ardUI() {
    for (auto s : backStack) {
        delete s;
    }
    delete currentActivity;
}


ardUI &ardUI::getInstance() {
    static ardUI instance;
    return instance;
}


void ardUI::callActivityOnCreate(activity* a) {
    switch (a->currentState) {
        // Before in lifecycle
        case activity::Launched:
            a->onCreate();
            break;
        // Current 
        case activity::Created:
        // Unreachable
        case activity::Restarted:
        case activity::Started:
        case activity::Resumed:
        case activity::Paused:
        case activity::Stopped:
        case activity::Destroyed:
            break;
    }
}


void ardUI::callActivityOnStart(activity* a) {
    switch (a->currentState) {
        // Before in lifecycle
        case activity::Launched:
            a->onCreate();
        case activity::Created:
        case activity::Restarted:
            a->onStart();
            break;
        // Current
        case activity::Started:
        // Unreachable
        case activity::Destroyed:
            break;
        // After in lifecycle
        case activity::Resumed:
            a->onPause();
        case activity::Paused:
            a->onStop();
        case activity::Stopped:
            a->onRestart();
            a->onStart();
            break;
    }
}


void ardUI::callActivityOnRestart(activity* a) {
    switch (a->currentState) {
        // Before in lifecycle
        case activity::Launched:
            a->onCreate();
        case activity::Created:
            a->onStart();
        case activity::Started:
            a->onResume();
        case activity::Resumed:
            a->onPause();
        case activity::Paused:
            a->onStop();
        case activity::Stopped:
            a->onRestart();
        // Current
        case activity::Restarted:
        // Unreachable
        case activity::Destroyed:
            break;
    }
}


void ardUI::callActivityOnResume(activity* a) {
    switch (a->currentState) {
        // Before in lifecycle
        case activity::Launched:
            a->onCreate();
        case activity::Created:
        case activity::Restarted:
            a->onStart();
        case activity::Started:
            a->onResume();
        // Current
        case activity::Resumed:
        // Unreachable
        case activity::Destroyed:
            break;
        // After in lifecycle
        case activity::Paused:
            a->onResume();
            break;
        case activity::Stopped:
            a->onRestart();
            a->onStart();
            a->onResume();
            break;
    }
}


void ardUI::callActivityOnPause(activity* a) {
    switch (a->currentState) {
        // Before in lifecycle
        case activity::Launched:
            a->onCreate();
        case activity::Created:
        case activity::Restarted:
            a->onStart();
        case activity::Started:
            a->onResume();
        case activity::Resumed:
            a->onPause();
        // Current
        case activity::Paused:
        // Unreachable
        case activity::Destroyed:
            break;
        // After in lifecycle
        case activity::Stopped:
            a->onRestart();
            a->onStart();
            a->onResume();
            a->onStop();
            break;
    }
}


void ardUI::callActivityOnStop(activity* a) {
    switch (a->currentState) {
        // Before in lifecycle
        case activity::Launched:
            a->onCreate();
        case activity::Created:
        case activity::Restarted:
            a->onStart();
        case activity::Started:
            a->onResume();
        case activity::Resumed:
            a->onPause();
        case activity::Paused:
            a->onStop();
        // Current
        case activity::Stopped:
        // Unreachable
        case activity::Destroyed:
            break;
    }
}


void ardUI::callActivityOnDestroy(activity* a) {
    switch (a->currentState) {
        // Before in lifecycle
        case activity::Launched:
            a->onCreate();
        case activity::Created:
        case activity::Restarted:
            a->onStart();
        case activity::Started:
            a->onResume();
        case activity::Resumed:
            a->onPause();
        case activity::Paused:
            a->onStop();
        case activity::Stopped:
            a->onDestroy();
        // Current
        case activity::Destroyed:
            break;
    }
}


activity& ardUI::getCurrentScreen() {
    return *getInstance().currentActivity;
}


void ardUI::back() {
    auto s {getInstance().currentActivity};

    if (s) {
        if (getInstance().currentDialog) {
            getInstance().currentDialog = nullptr;
            callActivityOnResume(s);
        }

        if (getInstance().backStack.length() > 0) {
            callActivityOnDestroy(s);
            delete s;

            s = getInstance().backStack.popFront();
            getInstance().currentActivity = s;
            callActivityOnResume(s);
        }
    }
}


void ardUI::showDialog(dialog& dialogToShow) {
    auto s {getInstance().currentActivity};

    if (s) {
        callActivityOnPause(s);
        getInstance().currentDialog = &dialogToShow;
    }
}


void ardUI::checkForActions() {
    if (ardUiDisplayIsClicked()) {
        static uint16_t x, y;
        ardUiDisplayClickLocation(x, y);
        //TODO: check for actions
    }
}


void ardUI::draw() {
    if (getInstance().currentDialog) {
        getInstance().currentDialog->draw();
    }

    if (getInstance().currentActivity) {
        getInstance().currentActivity->measure();  //TODO: remove
        getInstance().currentActivity->layout();
        getInstance().currentActivity->draw();
    }
}
