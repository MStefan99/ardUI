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
		static uint16_t lastX {event.targetX}, lastY {event.targetY};
		event.targetX = arduiDisplayGetClickX();
		event.targetY = arduiDisplayGetClickY();

		if (event.currentAction == Event::Action::NO_ACTION) {
			event.currentAction = Event::Action::CLICK;  // Register click

			lastX = event.targetX;  // Set last coords to current
			lastY = event.targetY;
#if VERBOSE
			Serial.println("Event registered");
#endif
		} else {
			actionTime += deltaTime;
			event.deltaX = (int16_t)(lastX - event.targetX);
			event.deltaY = (int16_t)(lastY - event.targetY);
		}
		if (event.currentAction == Event::Action::SCROLL) {
			// Handle scroll event every update
			if (ActivityManager::currentActivity) {
#if VERBOSE
				Serial.println("Scroll event dispatched");
#endif
				if (ActivityManager::currentActivity) {
					ActivityManager::currentActivity->handleEvent(event);
				}
			}
		} else if (actionTime >= LONG_CLICK_TIME) {
			event.currentAction = Event::Action::LONG_CLICK;  // Register long click
		}
		if (event.currentAction == Event::Action::CLICK && (
			((uint32_t)ABS(event.deltaX) * 1000 / deltaTime > SCROLL_SENSITIVITY) ||
			((uint32_t)ABS(event.deltaY) * 1000 / deltaTime > SCROLL_SENSITIVITY))) {
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
		actionTime = 0;
	}
}


void EventManager::draw() {
	ActivityManager::processWaitingActivities();
#ifdef VERBOSE
	Serial.println("Draw call");
#endif
	if (ActivityManager::currentActivity) {
		ActivityManager::currentActivity->measure();
		ActivityManager::currentActivity->layout();
		ActivityManager::currentActivity->draw();
	}
}
