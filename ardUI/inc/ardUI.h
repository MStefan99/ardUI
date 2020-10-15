//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_H
#define ARDUI_H


#include "platform.h"
#include "ardUI_config.h"
#include "llpi.h"

#include "activity.h"

#include "view.h"


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

	static void rewindActivityState(Activity* activity, Activity::state targetState);

	void operator =(ardUI const&) = delete;

	static void checkForActions();
	static void draw();

private:
	ardUI() = default;
	~ardUI();

	const uint16_t screenHeight {arduiDisplayGetHeight()};
	const uint16_t screenWidth {arduiDisplayGetWidth()};
	Activity* currentActivity {nullptr};
#if USING_STL
	std::list<Activity*> backStack {};
#else
	ardui::list<Activity*> backStack {};
#endif
};


template <class ActivityClass>
void ardUI::showScreen() {
	auto s {getInstance().currentActivity};
	if (s) {
		rewindActivityState(s, Activity::Stopped);
		getInstance().backStack.push_front(s);
		Serial.println("Screen appended to the stack");

		if (getInstance().backStack.size() > BACK_STACK_DEPTH) {
			Serial.println("Max stack depth reached, destroying last activity");
			auto lastScreen {getInstance().backStack.back()};
			getInstance().backStack.pop_back();
			rewindActivityState(lastScreen, Activity::Destroyed);
			delete lastScreen;
		}
	}
	s = new ActivityClass();
	getInstance().currentActivity = s;

	rewindActivityState(s, Activity::Resumed);
}


#define ardUI() ardUI::getInstance()  // Instantiates ardUI from "ardUI()" call (discouraged)

#endif //ARDUI_H
