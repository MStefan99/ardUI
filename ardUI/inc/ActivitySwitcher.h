//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_ACTIVITYSWITCHER_H
#define ARDUI_ACTIVITYSWITCHER_H

#include "Activity.h"


template <class ActivityClass>
void ActivityManager::switchActivity(const Bundle& extras,
																		 void (* onActivityResult)(int statusCode, Bundle resultData)) {
	if (currentActivity) {
		if (currentActivity->rootView) {
			currentActivity->rootView->invalidate();
		}
		currentActivity->rewindState(Activity::State::STOPPED);
		backList.push_back(currentActivity);
		Serial.println("Screen appended to the stack");

		if (backList.size() > BACK_STACK_DEPTH) {
			Serial.println("Max stack depth reached, destroying oldest activity");
			auto lastScreen {backList.front()};
			backList.pop_front();
			lastScreen->rewindState(Activity::State::DESTROYED);
			delete lastScreen;
		}
	}

	currentActivity = new ActivityClass {extras, onActivityResult};
	currentActivity->rewindState(Activity::State::RESUMED);
	ActivityManager::cleanup();
}


#endif //ARDUI_ACTIVITYSWITCHER_H
