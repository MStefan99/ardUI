//
// Created by MStefan99 on 11.11.20.
//

#include "EventManager.h"


#undef setup
#undef loop
#undef delay


void setup() {  // Default setup function will be used to initiate ardUI
	ardui::display::init();
	arduiUserSetup();  // Calling user setup function
	EventManager::update();
}


void loop() {  // ardUI core functions will be added to the loop function
	EventManager::update();
}


void EventManager::update(bool callUserLoop) {
	static uint32_t lastTouchRefresh, lastDisplayRefresh {1000 / REFRESH_RATE};
	uint32_t currentTime = millis();

	if (ABS(currentTime - lastDisplayRefresh) > 1000 / REFRESH_RATE) {
		EventManager::draw();  // Drawing UI elements
		lastDisplayRefresh = currentTime;
	}
	if (ABS(currentTime - lastTouchRefresh) > 1000 / TOUCH_RATE) {
		EventManager::checkForActions(currentTime - lastTouchRefresh);  // Checking for user interaction
		lastTouchRefresh = currentTime;
	}

	currentTime = millis();

	if (callUserLoop) {
		arduiUserLoop();  // Calling user loop function
	}

#if LOG_LEVEL >= LOG_INFO
	if (millis() - currentTime > 1000 / REFRESH_RATE) {
		Serial.println("Skipping frames, please ensure your loop doesn't perform any long operations");
	}
#endif

#if LOG_LEVEL >= LOG_VERBOSE
	Serial.println("Loop iteration");
#endif

#if SLOW_MODE && !defined(__EMSCRIPTEN__)
	delay(MIN(1000 / TOUCH_RATE, 1000 / REFRESH_RATE) + 50);
#endif
}


void arduiSmartDelay(uint32_t ms) {
	#if LOG_LEVEL >= LOG_INFO
	Serial.println("Please be careful when using sleep!");
	#endif

	auto startTime = millis();

	while (ABS(millis() - startTime) < ms) {
		EventManager::update(false);
		delay(MIN(1000 / TOUCH_RATE, 1000 / REFRESH_RATE));
	}
}


void EventManager::checkForActions(uint32_t deltaTime) {
	static Event event {};
	static uint32_t actionTime {0};

	if (ardui::display::isClicked()) {  // Detecting actions
		int16_t lastX {event._targetX}, lastY {event._targetY};
		event._targetX = ardui::display::getClickX();
		event._targetY = ardui::display::getClickY();

		if (event._currentAction == Event::Action::NO_ACTION) {
			event._currentAction = Event::Action::CLICK;  // Register click

			lastX = event._targetX;  // Set last coords to current
			lastY = event._targetY;
#if LOG_LEVEL >= LOG_VERBOSE
			Serial.println("Event registered");
#endif
		} else {
			actionTime += deltaTime;
			event._deltaX = (int16_t)(event._targetX - lastX);
			event._deltaY = (int16_t)(event._targetY - lastY);
		}
		if (event._currentAction == Event::Action::SCROLL) {
			// Handle scroll event every Update
			if (ActivityManager::_currentActivity) {
#if LOG_LEVEL >= LOG_VERBOSE
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
#if LOG_LEVEL >= LOG_VERBOSE
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
#if LOG_LEVEL >= LOG_VERBOSE
	Serial.println("Draw call");
#endif
	if (ActivityManager::_currentActivity) {
		auto displayWidth {ardui::display::getWidth()};
		auto displayHeight {ardui::display::getHeight()};

		ActivityManager::_currentActivity->measure(
				View::MeasureSpec {displayWidth, View::MeasureSpec::EXACTLY},
				View::MeasureSpec {displayHeight, View::MeasureSpec::EXACTLY});
		ActivityManager::_currentActivity->layout(0, 0, displayWidth, displayHeight);
		ActivityManager::_currentActivity->draw();
	}
}
