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


// Fallback is intended in the following state change functions
void ardUI::rewindActivityOnCreate(Activity* a) {
	switch (a->currentState) {
		case Activity::Created:  // Current

		case Activity::Restarted:  // Unreachable
		case Activity::Started:
		case Activity::Resumed:
		case Activity::Paused:
		case Activity::Stopped:
		case Activity::Destroyed:
			break;

		case Activity::Launched:  // Before in lifecycle
			a->create();
			break;
	}
}


void ardUI::rewindActivityOnStart(Activity* a) {
	switch (a->currentState) {
		case Activity::Started:  // Current

		case Activity::Destroyed:  // Unreachable
			break;

		case Activity::Launched:  // Before in lifecycle
			a->create();
		case Activity::Created:
		case Activity::Restarted:
			a->start();
			break;

		case Activity::Resumed:  // After in lifecycle
			a->pause();
		case Activity::Paused:
			a->stop();
		case Activity::Stopped:
			a->restart();
			a->start();
	}
}


void ardUI::rewindActivityOnRestart(Activity* a) {
	switch (a->currentState) {
		case Activity::Restarted:  // Current

		case Activity::Destroyed:  // Unreachable
			break;

		case Activity::Launched:// Before in lifecycle
			a->create();
		case Activity::Created:
			a->start();
		case Activity::Started:
			a->resume();
		case Activity::Resumed:
			a->pause();
		case Activity::Paused:
			a->stop();
		case Activity::Stopped:
			a->restart();
	}
}


void ardUI::rewindActivityOnResume(Activity* a) {
	switch (a->currentState) {
		case Activity::Resumed:  // Current

		case Activity::Destroyed:  // Unreachable
			break;

		case Activity::Launched:  // Before in lifecycle
			a->create();
		case Activity::Created:
		case Activity::Restarted:
			a->start();
		case Activity::Started:
		case Activity::Paused:  // After in lifecycle
			a->resume();
			break;

		case Activity::Stopped:
			a->restart();
			a->start();
			a->resume();
	}
}


void ardUI::rewindActivityOnPause(Activity* a) {
	switch (a->currentState) {
		case Activity::Paused:  // Current

		case Activity::Destroyed:  // Unreachable
			break;

		case Activity::Launched:  // Before in lifecycle
			a->create();
		case Activity::Created:
		case Activity::Restarted:
			a->start();
		case Activity::Started:
			a->resume();
		case Activity::Resumed:
			a->pause();
			break;

		case Activity::Stopped:  // After in lifecycle
			a->restart();
			a->start();
			a->resume();
			a->pause();
	}
}


void ardUI::rewindActivityOnStop(Activity* a) {
	switch (a->currentState) {
		case Activity::Stopped:  // Current

		case Activity::Destroyed:  // Unreachable
			break;

		case Activity::Launched:  // Before in lifecycle
			a->create();
		case Activity::Created:
		case Activity::Restarted:
			a->start();
		case Activity::Started:
			a->resume();
		case Activity::Resumed:
			a->pause();
		case Activity::Paused:
			a->stop();
	}
}


void ardUI::rewindActivityOnDestroy(Activity* a) {
	switch (a->currentState) {
		case Activity::Destroyed:  // Current
			break;

		case Activity::Launched:  // Before in lifecycle
			a->create();
		case Activity::Created:
		case Activity::Restarted:
			a->start();
		case Activity::Started:
			a->resume();
		case Activity::Resumed:
			a->pause();
		case Activity::Paused:
			a->stop();
		case Activity::Stopped:
			a->destroy();
	}
}


Activity& ardUI::getCurrentScreen() {
	return *getInstance().currentActivity;
}


void ardUI::back() {
	auto s {getInstance().currentActivity};

	if (s) {
		if (!getInstance().backStack.empty()) {
			rewindActivityOnDestroy(s);
			delete s;

			s = getInstance().backStack.back();
			getInstance().backStack.pop_front();
			getInstance().currentActivity = s;
			rewindActivityOnResume(s);
		}
	}
}


void ardUI::exit() {
	for (const auto& activity : getInstance().backStack) {
		rewindActivityOnDestroy(activity);
		delete activity;
	}
	getInstance().backStack.clear();

	if (getInstance().currentActivity) {
		rewindActivityOnDestroy(getInstance().currentActivity);
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
