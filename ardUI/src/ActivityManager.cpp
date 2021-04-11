//
// Created by MStefan99 on 11.11.20.
//

#include "ActivityManager.h"
#include "ActivitySwitcher.h"


Activity* ActivityManager::currentActivity {};
LIST<Activity*> ActivityManager::startingActivities {};
LIST<Activity*> ActivityManager::stoppingActivities {};
LIST<Activity*> ActivityManager::backList {};


void ActivityManager::stopActivity(Activity* activityToStop) {
	stoppingActivities.push_back(activityToStop);
}


void ActivityManager::back() {
	stopActivity(currentActivity);
}


void ActivityManager::reset() {
	for (auto a : backList) {
		finishActivity(a);
	}
}


void ActivityManager::finishActivity(Activity* activity) {
	if (activity) {
		if (activity->resultCallback) {
			activity->resultCallback(activity->status,
															 Bundle {activity->resultData});
		}
		activity->rewindState(Activity::State::DESTROYED);

		if (activity == currentActivity && !backList.empty()) {
			currentActivity = backList.back();
			backList.pop_back();
			currentActivity->rewindState(Activity::State::RESUMED);
		}
		delete activity;
	}
}


void ActivityManager::processWaitingActivities() {
	while (!stoppingActivities.empty() || !startingActivities.empty()) {
		cleanupActivities();
		startupActivities();
	}
}


void ActivityManager::startupActivities() {
	for (auto activity : startingActivities) {
		if (currentActivity) {
			if (currentActivity->rootView) {
				currentActivity->rootView->invalidate();
			}
			currentActivity->rewindState(Activity::State::STOPPED);
			backList.push_back(currentActivity);
			Serial.println("Screen appended to the stack");

			if (backList.size() > BACK_STACK_DEPTH) {
				Serial.println("Max stack depth reached, destroying oldest activity");
				auto lastActivity {backList.front()};
				backList.pop_front();
				finishActivity(lastActivity);
			}
		}

		currentActivity = activity;
		currentActivity->rewindState(Activity::State::RESUMED);
	}
	startingActivities.clear();
}


void ActivityManager::cleanupActivities() {
	for (auto a: stoppingActivities) {
		finishActivity(a);
		for (auto it = backList.begin(); it != backList.end(); ++it) {
			if (a == *it) {
				backList.erase(it);
				break;
			}
		}
	}
	stoppingActivities.clear();
}
