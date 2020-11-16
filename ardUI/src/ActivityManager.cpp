//
// Created by MStefan99 on 11.11.20.
//

#include "ActivityManager.h"
#include "ActivitySwitcher.h"


Activity* ActivityManager::currentActivity {};
LIST<Activity*> ActivityManager::backList {};


void ActivityManager::back() {
	if (currentActivity) {
		if (!backList.empty()) {
			currentActivity->rewindState(Activity::State::DESTROYED);
			delete currentActivity;

			currentActivity = backList.back();
			backList.pop_back();
			currentActivity->rewindState(Activity::State::RESUMED);
		}
	}
}


void ActivityManager::exit() {
	if (currentActivity) {
		currentActivity->rewindState(Activity::State::DESTROYED);
		delete currentActivity;
		currentActivity = nullptr;
	}

	while (!backList.empty()) {
		auto activity = backList.front();
		activity->rewindState(Activity::State::DESTROYED);
		delete activity;
		backList.pop_front();
	}
}
