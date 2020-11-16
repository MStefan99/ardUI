//
// Created by MStefan99 on 11.11.20.
//

#include "ActivityManager.h"
#include "ActivitySwitcher.h"


Activity* ActivityManager::currentActivity {};
LIST<Activity*> ActivityManager::activitiesToStop {};
LIST<Activity*> ActivityManager::backList {};


void ActivityManager::stopActivity(Activity* activityToStop) {
	activitiesToStop.push_back(activityToStop);
}


void ActivityManager::back() {
	if (currentActivity) {
		if (!backList.empty()) {
			auto prevActivity = backList.back();
			if (currentActivity->returnsResult) {
				prevActivity->onActivityResult(currentActivity->request,
																	 currentActivity->result,
																	 currentActivity->resultData);
			}
			currentActivity->rewindState(Activity::State::DESTROYED);
			delete currentActivity;

			currentActivity = backList.back();
			backList.pop_back();
			currentActivity->rewindState(Activity::State::RESUMED);
		}
	}
	cleanup();
}


void ActivityManager::reset() {
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


void ActivityManager::cleanup() {
	for (const auto& a: activitiesToStop) {
		if (a == currentActivity) {
			back();
		} else {
			for (auto it = backList.begin(); it != backList.end(); ++it) {
				if (a == *it) {
					backList.erase(it);
					break;
				}
			}
		}
	}
}
