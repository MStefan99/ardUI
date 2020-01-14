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
    delete currentActivity;
}


ardUI &ardUI::getApplicationContext() {
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
    return *getApplicationContext().currentActivity;
}


void ardUI::back() {
    auto s {getApplicationContext().currentActivity};

    if (s) {
        if (getApplicationContext().currentDialog) {
            getApplicationContext().currentDialog = nullptr;
            callActivityOnResume(s);
        }

        if (getApplicationContext().backStack.length() > 0) {
            callActivityOnDestroy(s);
            delete s;

            s = getApplicationContext().backStack.popLeft();
            getApplicationContext().currentActivity = s;
            callActivityOnResume(s);
        }
    }
}


void ardUI::showDialog(dialog& dialogToShow) {
    auto s {getApplicationContext().currentActivity};

    if (s) {
        callActivityOnPause(s);
        getApplicationContext().currentDialog = &dialogToShow;
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
    if (getApplicationContext().currentDialog) {
        getApplicationContext().currentDialog->draw();
    }

    if (getApplicationContext().currentActivity) {
        getApplicationContext().currentActivity->draw();
    }
}
