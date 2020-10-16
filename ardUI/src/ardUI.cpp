//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


#undef ardUI
#undef setup
#undef loop


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


void ardUI::rewindActivityState(Activity* a, Activity::state targetState) {
	if ((targetState <= Activity::state::Created && a->currentState > Activity::state::Created)
		|| (targetState < Activity::state::Destroyed && a->currentState == Activity::state::Destroyed)) {
		return;  // State unreachable
	}

	while (a->currentState != targetState) {
		switch (a->currentState) {
			case Activity::state::Launched:
				a->create();
				break;
			case Activity::state::Created:
			case Activity::state::Restarted:
				a->start();
				break;
			case Activity::state::Started:
				a->resume();
				break;
			case Activity::state::Resumed:
				a->pause();
				break;
			case Activity::state::Paused:
				if (targetState == Activity::state::Resumed) {
					a->resume();
				} else {
					a->stop();
				}
				break;
			case Activity::state::Stopped:
				if (targetState == Activity::state::Destroyed) {
					a->destroy();
				} else {
					a->restart();
				}
				break;

			case Activity::state::Destroyed:
				break;
		}
	}
}


Activity& ardUI::getCurrentScreen() {
	return *getInstance().currentActivity;
}


void ardUI::back() {
	auto s {getInstance().currentActivity};

	if (s) {
		if (!getInstance().backStack.empty()) {
			rewindActivityState(s, Activity::state::Destroyed);
			delete s;

			s = getInstance().backStack.back();
			getInstance().backStack.pop_front();
			getInstance().currentActivity = s;
			rewindActivityState(s, Activity::state::Resumed);
		}
	}
}


void ardUI::exit() {
	for (const auto& activity : getInstance().backStack) {
		rewindActivityState(activity, Activity::state::Destroyed);
		delete activity;
	}
	getInstance().backStack.clear();

	if (getInstance().currentActivity) {
		rewindActivityState(getInstance().currentActivity, Activity::state::Destroyed);
		delete getInstance().currentActivity;
		getInstance().currentActivity = nullptr;
	}
}


void ardUI::checkForActions() {
	static uint16_t x, y;
	static ardUI::action currentAction {ardUI::action::NO_ACTION};
	static uint16_t actionTicks {0};

	if (arduiDisplayIsClicked()) {  // Detecting actions
		static uint16_t lastX {x}, lastY {y};
		arduiDisplayClickLocation(x, y);
		++actionTicks;

		if (currentAction != ardUI::action::SCROLL &&
			actionTicks > LONG_CLICK_TIME * REFRESH_RATE / 1000) {
			currentAction = ardUI::action::LONG_CLICK;
		}
		if (lastX - x > 10 || lastX - x < -10 ||
			lastY - y > 10 || lastY - y < -10) {
			currentAction = ardUI::action::SCROLL;
		}
		if (currentAction == ardUI::action::NO_ACTION) {
			currentAction = ardUI::action::CLICK;
		} else if (currentAction == ardUI::action::SCROLL) {
			// TODO: handle scroll action
		}
	} else {
		// TODO: handle actions
		currentAction = ardUI::action::NO_ACTION;
		actionTicks = 0;
	}
}


void ardUI::draw() {
	if (getInstance().currentActivity) {
		getInstance().currentActivity->measure();
		getInstance().currentActivity->layout();
		getInstance().currentActivity->draw();
	}
}
