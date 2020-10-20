//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_H
#define ARDUI_H


#include "platform.h"
#include "llpi.h"
#include "ardUI_config.h"

#include "Activity.h"
#include "Event.h"
#include "View.h"

#include LIST_H
#include MAP_H


// Hiding standard Arduino functions for correct operation of ardUI
void arduiUserSetup();  // User "setup()" function will be replaced by this custom function
void arduiUserLoop();  // User "loop()" function will be replaced by this custom function

#define setup() arduiUserSetup()
#define loop() arduiUserLoop()

class ardUI {
public:
	ardUI() = delete;

	template <class ActivityClass>
	static void showScreen();
	static void back();
	static void exit();

	static void setViewName(View* view, const String& name);
	static View* getViewByName(const String& name);

	static void checkForActions();
	static void draw();

private:
	static void rewindActivityState(Activity* activity, Activity::State targetState);

	const uint16_t screenHeight {arduiDisplayGetHeight()};
	const uint16_t screenWidth {arduiDisplayGetWidth()};

	static Activity* currentActivity;
	static LIST<Activity*> backList;
	static MAP<String, View*> viewMap;
};


template <class ActivityClass>
void ardUI::showScreen() {
	if (currentActivity) {
		rewindActivityState(currentActivity, Activity::State::STOPPED);
		backList.push_back(currentActivity);
		Serial.println("Screen appended to the stack");

		if (backList.size() > BACK_STACK_DEPTH) {
			Serial.println("Max stack depth reached, destroying oldest activity");
			auto lastScreen {backList.front()};
			backList.pop_front();
			rewindActivityState(lastScreen, Activity::State::DESTROYED);
			delete lastScreen;
		}
	}
	currentActivity = new ActivityClass {};

	rewindActivityState(currentActivity, Activity::State::RESUMED);
}


#endif //ARDUI_H
