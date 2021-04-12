//
// Created by MStefan99 on 11.11.20.
//

#ifndef ARDUI_EVENTMANAGER_H
#define ARDUI_EVENTMANAGER_H


#include "platform.h"
#include "llpi.h"
#include "Event.h"
#include "Activity.h"
#include "ActivityManager.h"


// Hiding standard Arduino functions for correct operation of ardUI
void arduiUserSetup();  // User "setup()" function will be replaced by this custom function
void arduiUserLoop();  // User "loop()" function will be replaced by this custom function

#define setup() arduiUserSetup()
#define loop() arduiUserLoop()

class EventManager {
public:
	EventManager() = delete;

	static void checkForActions(uint32_t deltaTime);
	static void draw();
};

#endif //ARDUI_EVENTMANAGER_H
