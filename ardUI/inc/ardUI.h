//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_H
#define ARDUI_H


#include "platform.h"
#include "ardUI_config.h"
#include "llpi.h"

#include "activity.h"
#include "dialog.h"  //TODO: move to activity

#include "view.h"
#include "text_view.h"
#include "button_view.h"

#include "view_group.h"
#include "linear_layout.h"


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
	static void showDialog(Dialog& dialogToShow);
	static void back();
	static void exit();

	static void callActivityOnCreate(Activity* activity);
	static void callActivityOnStart(Activity* activity);
	static void callActivityOnRestart(Activity* activity);
	static void callActivityOnResume(Activity* activity);
	static void callActivityOnPause(Activity* activity);
	static void callActivityOnStop(Activity* activity);
	static void callActivityOnDestroy(Activity* activity);

	void operator =(ardUI const&) = delete;

	static void checkForActions();
	static void draw();

private:
	ardUI() = default;
	~ardUI();

	const uint16_t screenHeight {arduiDisplayGetHeight()};
	const uint16_t screenWidth {arduiDisplayGetWidth()};
	Activity* currentActivity {nullptr};
	Dialog* currentDialog {nullptr};
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
		callActivityOnStop(s);
		getInstance().backStack.push_front(s);
		Serial.println("Screen appended to the stack");

		if (getInstance().backStack.size() > BACK_STACK_DEPTH) {
			Serial.println("Max stack depth reached, destroying last activity");
			auto lastScreen {getInstance().backStack.back()};
			getInstance().backStack.pop_back();
			callActivityOnDestroy(lastScreen);
			delete lastScreen;
		}
	}
	s = new ActivityClass();
	getInstance().currentActivity = s;

	callActivityOnResume(s);
}


#define ardUI() ardUI::getInstance()  // Instantiates ardUI from "ardUI()" call (discouraged)

#endif //ARDUI_H
