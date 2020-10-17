//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_H
#define ARDUI_H


#include "platform.h"
#include "ardUI_config.h"
#include "llpi.h"

#include "activity.h"
#include "event.h"
#include "view.h"

#include LIST_H
#include MAP_H


// Hiding standard Arduino functions for correct operation of ardUI
void arduiUserSetup();  // User "setup()" function will be replaced by this custom function
void arduiUserLoop();  // User "loop()" function will be replaced by this custom function

#define setup() arduiUserSetup()
#define loop() arduiUserLoop()

class ardUI {
public:
	explicit ardUI(ardUI const&) = delete;

	static ardUI& getInstance();
	static Activity& getCurrentScreen();

	template <class ScreenClass>
	static void showScreen();
	static void back();
	static void exit();

	static void setViewName(View* view, const String& name);
	static View* getViewByName(const String& name);

	static void checkForActions();
	static void draw();

	void operator =(ardUI const&) = delete;

private:
	ardUI() = default;
	~ardUI();

	static void rewindActivityState(Activity* activity, Activity::State targetState);

	const uint16_t screenHeight {arduiDisplayGetHeight()};
	const uint16_t screenWidth {arduiDisplayGetWidth()};

	static Activity* currentActivity;
	static LIST<Activity*> backStack;
	static MAP<String, View*> viewMap;
};


template <class ActivityClass>
void ardUI::showScreen() {
	auto s {currentActivity};
	if (s) {
		rewindActivityState(s, Activity::State::STOPPED);
		backStack.push_front(s);
		Serial.println("Screen appended to the stack");

		if (backStack.size() > BACK_STACK_DEPTH) {
			Serial.println("Max stack depth reached, destroying last activity");
			auto lastScreen {backStack.back()};
			backStack.pop_back();
			rewindActivityState(lastScreen, Activity::State::DESTROYED);
			delete lastScreen;
		}
	}
	s = new ActivityClass();
	currentActivity = s;

	rewindActivityState(s, Activity::State::RESUMED);
}


#define ardUI() ardUI::getInstance()  // Instantiates ardUI from "ardUI()" call (discouraged)

#endif //ARDUI_H
