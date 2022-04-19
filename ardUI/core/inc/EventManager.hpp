//
// Created by MStefan99 on 11.11.20.
//

#ifndef ARDUI_EVENTMANAGER_HPP
#define ARDUI_EVENTMANAGER_HPP

#include "platform.hpp"
#include DISPLAY_H

#include "Event.hpp"
#include "Activity.hpp"
#include "ActivityManager.hpp"


// Hiding standard Arduino functions for correct operation of ardUI
void arduiUserSetup();  // User "setup()" function will be replaced by this custom function
void arduiUserLoop();  // User "loop()" function will be replaced by this custom function

#define setup() arduiUserSetup()
#define loop() arduiUserLoop()

#if SMART_DELAY
void arduiSmartDelay(uint32_t ms);  // This method replaces the original "delay" function to let ardUI run when called
#define delay(ms) arduiSmartDelay(ms)
#endif

class EventManager final {
public:
	EventManager() = delete;

	static void update(bool forceDraw = false, bool callUserLoop = false);

private:
	static void checkForActions(uint32_t deltaTime);
	static void draw();
};

#endif //ARDUI_EVENTMANAGER_HPP
