//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


#undef ardUI
#undef setup
#undef loop

Activity* ardUI::currentActivity {};
LIST<Activity*> ardUI::backStack {};
MAP<String, View*> ardUI::viewMap {};


void setup() {  // Default setup function will be used to initiate ardUI
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
		ardUI::draw();  // Drawing UI elements
		lastDisplayRefresh = currentTime;
	}
	if (currentTime - lastTouchRefresh > 1000 / TOUCH_RATE) {
		ardUI::checkForActions();  // Checking for user interaction
		lastTouchRefresh = currentTime;
	}

	arduiUserLoop();  // Calling user loop function
}


ardUI::~ardUI() {  // Should never be called since instance is declared static
	for (auto s : backStack) {
		delete s;
	}
	delete currentActivity;
}


ardUI& ardUI::getInstance() {
	static ardUI instance;
	return instance;
}


void ardUI::rewindActivityState(Activity* a, Activity::State targetState) {
	if ((targetState <= Activity::State::CREATED && a->currentState > Activity::State::CREATED)
		|| (targetState < Activity::State::DESTROYED && a->currentState == Activity::State::DESTROYED)) {
		return;  // State unreachable
	}

	while (a->currentState != targetState) {
		switch (a->currentState) {
			case Activity::State::LAUNCHED:
				a->create();
				break;
			case Activity::State::CREATED:
			case Activity::State::RESTARTED:
				a->start();
				break;
			case Activity::State::STARTED:
				a->resume();
				break;
			case Activity::State::RESUMED:
				a->pause();
				break;
			case Activity::State::PAUSED:
				if (targetState == Activity::State::RESUMED) {
					a->resume();
				} else {
					a->stop();
				}
				break;
			case Activity::State::STOPPED:
				if (targetState == Activity::State::DESTROYED) {
					a->destroy();
				} else {
					a->restart();
				}
				break;

			case Activity::State::DESTROYED:
				break;
		}
	}
}


Activity& ardUI::getCurrentScreen() {
	return *currentActivity;
}


void ardUI::back() {
	auto s {currentActivity};

	if (s) {
		if (!backStack.empty()) {
			rewindActivityState(s, Activity::State::DESTROYED);
			delete s;

			s = backStack.back();
			backStack.pop_front();
			currentActivity = s;
			rewindActivityState(s, Activity::State::RESUMED);
		}
	}
}


void ardUI::exit() {
	for (const auto& activity : backStack) {
		rewindActivityState(activity, Activity::State::DESTROYED);
		delete activity;
	}
	backStack.clear();

	if (currentActivity) {
		rewindActivityState(currentActivity, Activity::State::DESTROYED);
		delete currentActivity;
		currentActivity = nullptr;
	}
}


void ardUI::checkForActions() {
	static Event event {};
	static uint16_t actionTicks {0};

	if (arduiDisplayIsClicked()) {  // Detecting actions
		static uint16_t lastX {event.targetX}, lastY {event.targetY};
		arduiDisplayGetClickLocation(event.targetX, event.targetY);
		++actionTicks;

		if (event.currentAction == Event::Action::NO_ACTION) {
			event.currentAction = Event::Action::CLICK;  // Register click
#if VERBOSE
			Serial.println("Event registered");
#endif
		} else {
			event.deltaX = lastX - event.targetX;
			event.deltaY = lastY = event.targetY;
		}
		if (event.currentAction == Event::Action::SCROLL) {
			// Handle scroll event every tick
			if (currentActivity) {
#if VERBOSE
				Serial.println("Scroll event dispatched");
#endif
				currentActivity->handleEvent(event);
			}
		} else if (actionTicks > LONG_CLICK_TIME * REFRESH_RATE / 1000) {
			event.currentAction = Event::Action::LONG_CLICK;  // Register long click
		}
		if ((event.deltaX > SCROLL_SENSITIVITY) ||
			(event.deltaX < -SCROLL_SENSITIVITY) ||
			(event.deltaY > SCROLL_SENSITIVITY) ||
			(event.deltaY < -SCROLL_SENSITIVITY)) {
			event.currentAction = Event::Action::SCROLL;  // Register scroll
		}
	} else {
#if VERBOSE
		Serial.println("Event dispatched");
#endif
		if (currentActivity) {  // Touch over, handle event
			currentActivity->handleEvent(event);
		}
		event.currentAction = Event::Action::NO_ACTION;
		actionTicks = 0;
	}
}


void ardUI::draw() {
	if (currentActivity) {
		currentActivity->measure();
		currentActivity->layout();
		currentActivity->draw();
	}
}


void ardUI::setViewName(View* view, const String& name) {
	viewMap[name] = view;
}


View* ardUI::getViewByName(const String& name) {
	return viewMap[name];
}
