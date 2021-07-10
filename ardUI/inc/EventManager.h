//
// Created by MStefan99 on 11.11.20.
//

#ifndef ARDUI_EVENTMANAGER_H
#define ARDUI_EVENTMANAGER_H

#include "platform.h"
#include DISPLAY_H

#include "Event.h"
#include "Activity.h"
#include "ActivityManager.h"


// Hiding standard Arduino functions for correct operation of ardUI
void arduiUserSetup();  // User "setup()" function will be replaced by this custom function
void arduiUserLoop();  // User "loop()" function will be replaced by this custom function
void update(bool callUserLoop = true);

#define setup() arduiUserSetup()
#define loop() arduiUserLoop()

// Hybrid sleep
#if SMART_DELAY
void arduiSmartDelay(uint32_t ms);  // This method replaces the original "delay" function to let ardUI run when called

#define delay(ms) arduiSmartDelay(ms)
#endif

class EventManager {
public:
	EventManager() = delete;

	static void checkForActions(uint32_t deltaTime);
	static void draw();
};

#endif //ARDUI_EVENTMANAGER_H
