//
// Created by MStefan99 on 11.11.20.
//

#include "EventManager.h"


#undef ardUI
#undef setup
#undef loop


void setup() {  // Default setup function will be used to initiate ardUI
	arduiDisplayInit();
	arduiUserSetup();  // Calling user setup function
}


void loop() {  // ardUI core functions will be added to the loop function
	static uint16_t lastDisplayRefresh, lastTouchRefresh;

	uint16_t currentTime = millis();

	if (currentTime < lastDisplayRefresh) {
		lastDisplayRefresh = 0;
	}
	if (currentTime < lastTouchRefresh) {
		lastTouchRefresh = 0;
	}

	if (currentTime - lastDisplayRefresh > 1000 / REFRESH_RATE) {
		EventManager::draw();  // Drawing UI elements
		lastDisplayRefresh = currentTime;
	}
	if (currentTime - lastTouchRefresh > 1000 / TOUCH_RATE) {
		EventManager::checkForActions();  // Checking for user interaction
		lastTouchRefresh = currentTime;
	}

	arduiUserLoop();  // Calling user loop function

#ifdef VERBOSE
	Serial.println("Loop iteration");
#endif
#ifdef DEBUG
	delay(1000 / REFRESH_RATE + 100);
#endif
}


void EventManager::checkForActions() {
	static Event event {};
	static uint16_t actionTicks {0};

	if (arduiDisplayIsClicked()) {  // Detecting actions
		static uint16_t lastX {event.targetX}, lastY {event.targetY};
		arduiDisplayGetClickLocation(event.targetX, event.targetY);
		++actionTicks;

		if (event.currentAction == Event::Action::NO_ACTION) {
			event.currentAction = Event::Action::CLICK;  // Register click

			lastX = event.targetX;  // Set last coords to current
			lastY = event.targetY;
#if VERBOSE
			Serial.println("Event registered");
#endif
		} else {
			event.deltaX = lastX - event.targetX;
			event.deltaY = lastY - event.targetY;
		}
		if (event.currentAction == Event::Action::SCROLL) {
			// Handle scroll event every tick
			if (ActivityManager::currentActivity) {
#if VERBOSE
				Serial.println("Scroll event dispatched");
#endif
				if (ActivityManager::currentActivity) {
					ActivityManager::currentActivity->handleEvent(event);
				}
			}
		} else if (actionTicks == LONG_CLICK_TIME * TOUCH_RATE / 1000) {
			event.currentAction = Event::Action::LONG_CLICK;  // Register long click
		}
		if (event.currentAction == Event::Action::CLICK && (
			(event.deltaX > SCROLL_SENSITIVITY) ||
			(event.deltaX < -SCROLL_SENSITIVITY) ||
			(event.deltaY > SCROLL_SENSITIVITY) ||
			(event.deltaY < -SCROLL_SENSITIVITY))) {
			event.currentAction = Event::Action::SCROLL;  // Register scroll
		}
	} else if (event.currentAction != Event::Action::NO_ACTION) {
#if VERBOSE
		Serial.println("Event dispatched");
#endif
		if (ActivityManager::currentActivity) {  // Touch over, handle event
			ActivityManager::currentActivity->handleEvent(event);
		}
		event.currentAction = Event::Action::NO_ACTION;
		actionTicks = 0;
	}
}


void EventManager::draw() {
#ifdef VERBOSE
	Serial.println("Draw call");
#endif
	if (ActivityManager::currentActivity) {
		ActivityManager::currentActivity->measure();
		ActivityManager::currentActivity->layout();
		ActivityManager::currentActivity->draw();
	}
}
