//
// Created by MStefan99 on 11.11.20.
//

#include "EventManager.h"


#undef ardUI
#undef setup
#undef loop

#define ABS(x) (x > 0? x : -x)


void setup() {  // Default setup function will be used to initiate ardUI
	arduiDisplayInit();
	arduiUserSetup();  // Calling user setup function
	EventManager::draw();
}


void loop() {  // ardUI core functions will be added to the loop function
	static uint32_t lastTouchRefresh, lastDisplayRefresh;
	uint32_t currentTime = millis();

	if (currentTime < lastTouchRefresh) {
		lastTouchRefresh = 0;
	}
	if (currentTime < lastDisplayRefresh) {
		lastDisplayRefresh = 0;
	}

	if (currentTime - lastDisplayRefresh > 1000 / REFRESH_RATE) {
		EventManager::draw();  // Drawing UI elements
		lastDisplayRefresh = currentTime;
	}
	if (currentTime - lastTouchRefresh > 1000 / TOUCH_RATE) {
		EventManager::checkForActions(currentTime - lastTouchRefresh);  // Checking for user interaction
		lastTouchRefresh = currentTime;
	}

	currentTime = millis();

	arduiUserLoop();  // Calling user loop function

	if (millis() - currentTime > 1000 / REFRESH_RATE) {
		Serial.println("Skipping frames, please ensure your loop doesn't perform any long operations");
	}

#ifdef VERBOSE
	Serial.println("Loop iteration");
#endif
#ifdef DEBUG
	delay(1000 / REFRESH_RATE + 100);
#endif
}


void EventManager::checkForActions(uint32_t deltaTime) {
	static Event event {};
	static uint32_t actionTime {0};

	if (arduiDisplayIsClicked()) {  // Detecting actions
		static uint16_t lastX {event._targetX}, lastY {event._targetY};
		event._targetX = arduiDisplayGetClickX();
		event._targetY = arduiDisplayGetClickY();

		if (event._currentAction == Event::Action::NO_ACTION) {
			event._currentAction = Event::Action::CLICK;  // Register click

			lastX = event._targetX;  // Set last coords to current
			lastY = event._targetY;
#if VERBOSE
			Serial.println("Event registered");
#endif
		} else {
			actionTime += deltaTime;
			event._deltaX = (int16_t)(lastX - event._targetX);
			event._deltaY = (int16_t)(lastY - event._targetY);
		}
		if (event._currentAction == Event::Action::SCROLL) {
			// Handle scroll event every update
			if (ActivityManager::_currentActivity) {
#if VERBOSE
				Serial.println("Scroll event dispatched");
#endif
				if (ActivityManager::_currentActivity) {
					ActivityManager::_currentActivity->handleEvent(event);
				}
			}
		} else if (actionTime >= LONG_CLICK_TIME) {
			event._currentAction = Event::Action::LONG_CLICK;  // Register long click
		}
		if (event._currentAction == Event::Action::CLICK && (
																													((uint32_t)ABS(event._deltaX) * 1000 / deltaTime > SCROLL_SENSITIVITY) ||
																													((uint32_t)ABS(event._deltaY) * 1000 / deltaTime > SCROLL_SENSITIVITY))) {
			event._currentAction = Event::Action::SCROLL;  // Register scroll
		}
	} else if (event._currentAction != Event::Action::NO_ACTION) {
#if VERBOSE
		Serial.println("Event dispatched");
#endif
		if (ActivityManager::_currentActivity) {  // Touch over, handle event
			ActivityManager::_currentActivity->handleEvent(event);
		}
		event._currentAction = Event::Action::NO_ACTION;
		actionTime = 0;
	}
}


void EventManager::draw() {
	ActivityManager::processWaitingActivities();
#ifdef VERBOSE
	Serial.println("Draw call");
#endif
	if (ActivityManager::_currentActivity) {
		ActivityManager::_currentActivity->measure();
		ActivityManager::_currentActivity->layout();
		ActivityManager::_currentActivity->draw();
	}
}
