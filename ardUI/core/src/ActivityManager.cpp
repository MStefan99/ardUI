//
// Created by MStefan99 on 11.11.20.
//

#include "ActivityManager.h"
#include "ActivitySwitcher.h"


Activity* ActivityManager::_currentActivity {};
TL_NS::list<Activity*> ActivityManager::_startingActivities {};
TL_NS::list<Activity*> ActivityManager::_stoppingActivities {};
TL_NS::list<Activity*> ActivityManager::_backList {};


void ActivityManager::stopActivity(Activity* activityToStop) {
	_stoppingActivities.push_back(activityToStop);
}


void ActivityManager::back() {
	if (_currentActivity->_dialog) {
		_currentActivity->dismissDialog();
	} else {
		stopActivity(_currentActivity);
	}
}


void ActivityManager::reset() {
	stopActivity(_currentActivity);
	for (auto a : _backList) {
		stopActivity(a);
	}
}


void ActivityManager::finishActivity(Activity* activity) {
	if (activity) {
		activity->rewindState(Activity::State::DESTROYED);

		if (activity == _currentActivity) {
			if (!_backList.empty()) {
				_currentActivity = _backList.back();
				if (activity->_resultCallback) {
					activity->_resultCallback(activity->_status, Bundle {activity->_resultData});
				}
				_backList.pop_back();
				_currentActivity->rewindState(Activity::State::RESUMED);
			} else {
				_currentActivity = nullptr;
			}
		}
		_backList.remove(activity);
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

			if (_backList.size() > BACK_STACK_DEPTH) {
				#if LOG_LEVEL >= LOG_WARNING
				Serial.println("Max stack depth reached, destroying oldest activity");
				#endif
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
	for (auto a : _stoppingActivities) {
		finishActivity(a);
	}

	_stoppingActivities.clear();
}
