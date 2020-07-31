//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


#undef ardUI
#undef setup
#undef loop


void setup() {  // Default setup function will be used to initiate ardUI1
	arduiUserSetup();  // Calling user setup routine
}


void loop() {  // ardUI1 core functions will be added to the loop function
	ardUI::draw();
	ardUI::checkForActions();
	arduiUserLoop();
}


ardUI::~ardUI() {
	for (auto s : backStack) {
		delete s;
	}
	delete currentActivity;
}


ardUI &ardUI::getInstance() {
	static ardUI instance;
	return instance;
}


void ardUI::callActivityOnCreate(Activity* a) {
	switch (a->currentState) {
		// Before in lifecycle
		case Activity::Launched:
			a->onCreate();
			break;
		// Current
		case Activity::Created:
		// Unreachable
		case Activity::Restarted:
		case Activity::Started:
		case Activity::Resumed:
		case Activity::Paused:
		case Activity::Stopped:
		case Activity::Destroyed:
			break;
	}
}


void ardUI::callActivityOnStart(Activity* a) {
	switch (a->currentState) {
		// Before in lifecycle
		case Activity::Launched:
			a->onCreate();
		case Activity::Created:
		case Activity::Restarted:
			a->onStart();
			break;
		// Current
		case Activity::Started:
		// Unreachable
		case Activity::Destroyed:
			break;
		// After in lifecycle
		case Activity::Resumed:
			a->onPause();
		case Activity::Paused:
			a->onStop();
		case Activity::Stopped:
			a->onRestart();
			a->onStart();
			break;
	}
}


void ardUI::callActivityOnRestart(Activity* a) {
	switch (a->currentState) {
		// Before in lifecycle
		case Activity::Launched:
			a->onCreate();
		case Activity::Created:
			a->onStart();
		case Activity::Started:
			a->onResume();
		case Activity::Resumed:
			a->onPause();
		case Activity::Paused:
			a->onStop();
		case Activity::Stopped:
			a->onRestart();
		// Current
		case Activity::Restarted:
		// Unreachable
		case Activity::Destroyed:
			break;
	}
}


void ardUI::callActivityOnResume(Activity* a) {
	switch (a->currentState) {
		// Before in lifecycle
		case Activity::Launched:
			a->onCreate();
		case Activity::Created:
		case Activity::Restarted:
			a->onStart();
		case Activity::Started:
			a->onResume();
		// Current
		case Activity::Resumed:
		// Unreachable
		case Activity::Destroyed:
			break;
		// After in lifecycle
		case Activity::Paused:
			a->onResume();
			break;
		case Activity::Stopped:
			a->onRestart();
			a->onStart();
			a->onResume();
			break;
	}
}


void ardUI::callActivityOnPause(Activity* a) {
	switch (a->currentState) {
		// Before in lifecycle
		case Activity::Launched:
			a->onCreate();
		case Activity::Created:
		case Activity::Restarted:
			a->onStart();
		case Activity::Started:
			a->onResume();
		case Activity::Resumed:
			a->onPause();
		// Current
		case Activity::Paused:
		// Unreachable
		case Activity::Destroyed:
			break;
		// After in lifecycle
		case Activity::Stopped:
			a->onRestart();
			a->onStart();
			a->onResume();
			a->onStop();
			break;
	}
}


void ardUI::callActivityOnStop(Activity* a) {
	switch (a->currentState) {
		// Before in lifecycle
		case Activity::Launched:
			a->onCreate();
		case Activity::Created:
		case Activity::Restarted:
			a->onStart();
		case Activity::Started:
			a->onResume();
		case Activity::Resumed:
			a->onPause();
		case Activity::Paused:
			a->onStop();
		// Current
		case Activity::Stopped:
		// Unreachable
		case Activity::Destroyed:
			break;
	}
}


void ardUI::callActivityOnDestroy(Activity* a) {
	switch (a->currentState) {
		// Before in lifecycle
		case Activity::Launched:
			a->onCreate();
		case Activity::Created:
		case Activity::Restarted:
			a->onStart();
		case Activity::Started:
			a->onResume();
		case Activity::Resumed:
			a->onPause();
		case Activity::Paused:
			a->onStop();
		case Activity::Stopped:
			a->onDestroy();
		// Current
		case Activity::Destroyed:
			break;
	}
}


Activity& ardUI::getCurrentScreen() {
	return *getInstance().currentActivity;
}


void ardUI::back() {
	auto s {getInstance().currentActivity};

	if (s) {
		if (getInstance().currentDialog) {
			getInstance().currentDialog = nullptr;
			callActivityOnResume(s);
		}

		if (!getInstance().backStack.empty()) {
			callActivityOnDestroy(s);
			delete s;

			s = getInstance().backStack.back();
			getInstance().backStack.pop_front();
			getInstance().currentActivity = s;
			callActivityOnResume(s);
		}
	}
}


void ardUI::showDialog(Dialog& dialogToShow) {
	auto s {getInstance().currentActivity};

	if (s) {
		callActivityOnPause(s);
		getInstance().currentDialog = &dialogToShow;
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
	if (getInstance().currentDialog) {
		getInstance().currentDialog->draw();
	}

	if (getInstance().currentActivity) {
		getInstance().currentActivity->measure();  //TODO: remove
		getInstance().currentActivity->layout();
		getInstance().currentActivity->draw();
	}
}
