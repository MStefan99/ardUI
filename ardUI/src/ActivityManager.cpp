//
// Created by MStefan99 on 11.11.20.
//

#include "ActivityManager.h"
#include "ActivitySwitcher.h"


Activity* ActivityManager::_currentActivity {};
LIST<Activity*> ActivityManager::_startingActivities {};
LIST<Activity*> ActivityManager::_stoppingActivities {};
LIST<Activity*> ActivityManager::_backList {};


void ActivityManager::stopActivity(Activity* activityToStop) {
	_stoppingActivities.push_back(activityToStop);
}


void ActivityManager::back() {
	stopActivity(_currentActivity);
}


void ActivityManager::reset() {
	for (auto a : _backList) {
		finishActivity(a);
	}
}


void ActivityManager::finishActivity(Activity* activity) {
	if (activity) {
		activity->rewindState(Activity::State::DESTROYED);

		if (activity == _currentActivity && !_backList.empty()) {
			_currentActivity = _backList.back();
			if (activity->_resultCallback) {
				activity->_resultCallback(activity->_status,
						Bundle {activity->_resultData});
			}
			_backList.pop_back();
			_currentActivity->rewindState(Activity::State::RESUMED);
		}
		delete activity;
	}
}


void ActivityManager::processWaitingActivities() {
	while (!_stoppingActivities.empty() || !_startingActivities.empty()) {
		cleanupActivities();
		startupActivities();
	}
}


void ActivityManager::startupActivities() {
	for (auto activity : _startingActivities) {
		if (_currentActivity) {
			if (_currentActivity->_rootView) {
				_currentActivity->_rootView->invalidate();
			}
			_currentActivity->rewindState(Activity::State::STOPPED);
			_backList.push_back(_currentActivity);
			Serial.println("Screen appended to the stack");

			if (_backList.size() > BACK_STACK_DEPTH) {
				Serial.println("Max stack depth reached, destroying oldest activity");
				auto lastActivity {_backList.front()};
				_backList.pop_front();
				finishActivity(lastActivity);
			}
		}

		_currentActivity = activity;
		_currentActivity->rewindState(Activity::State::RESUMED);
	}
	_startingActivities.clear();
}


void ActivityManager::cleanupActivities() {
	for (auto a: _stoppingActivities) {
		finishActivity(a);

		auto it = _backList.begin();
		while (it != _backList.end()) {
			if (a == *it) {
				it = _backList.erase(it);
			} else {
				++it;
			}
		}
	}
	_stoppingActivities.clear();
}
