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
	ardUI::draw();  // Drawing UI elements
	ardUI::checkForActions();  // Checking for user interaction
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
	if ((targetState <= Activity::Created && a->currentState > Activity::Created)
		|| (targetState < Activity::Destroyed && a->currentState == Activity::Destroyed)) {
		return;  // State unreachable
	}

	while (a->currentState != targetState) {
		switch (a->currentState) {
			case Activity::Launched:
				a->create();
				break;
			case Activity::Created:
			case Activity::Restarted:
				a->start();
				break;
			case Activity::Started:
				a->resume();
				break;
			case Activity::Resumed:
				a->pause();
				break;
			case Activity::Paused:
				if (targetState == Activity::Resumed) {
					a->resume();
				} else {
					a->stop();
				}
				break;
			case Activity::Stopped:
				if (targetState == Activity::Destroyed) {
					a->destroy();
				} else {
					a->restart();
				}
				break;

			case Activity::Destroyed:
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
			rewindActivityState(s, Activity::Destroyed);
			delete s;

			s = getInstance().backStack.back();
			getInstance().backStack.pop_front();
			getInstance().currentActivity = s;
			rewindActivityState(s, Activity::Resumed);
		}
	}
}


void ardUI::exit() {
	for (const auto& activity : getInstance().backStack) {
		rewindActivityState(activity, Activity::Destroyed);
		delete activity;
	}
	getInstance().backStack.clear();

	if (getInstance().currentActivity) {
		rewindActivityState(getInstance().currentActivity, Activity::Destroyed);
		delete getInstance().currentActivity;
		getInstance().currentActivity = nullptr;
	}
}


void ardUI::checkForActions() {
	if (arduiDisplayIsClicked()) {
		static uint16_t x, y;
		arduiDisplayClickLocation(x, y);
		//TODO: check for actions
	}
}


void ardUI::draw() {
	if (getInstance().currentActivity) {
		getInstance().currentActivity->measure();  //TODO: remove
		getInstance().currentActivity->layout();
		getInstance().currentActivity->draw();
	}
}
