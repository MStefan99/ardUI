//
// Created by MStefan99 on 11.11.20.
//

#ifndef ARDUI_ACTIVITYMANAGER_H
#define ARDUI_ACTIVITYMANAGER_H

#include "platform.h"
#include LIST_H

#include "Bundle.h"


class Activity;

class ActivityManager final {
public:
	ActivityManager() = delete;

private:
	template <class ActivityClass>
	static void startActivity(const Bundle& extras = {},
			void (* onActivityResult)(int statusCode, Bundle resultData) = {});
	static void stopActivity(Activity* activityToStop);
	static void back();
	static void reset();

	static void processWaitingActivities();

	// Internal methods, don't use outside ActivityManager
	static void finishActivity(Activity* activity);
	static void cleanupActivities();
	static void startupActivities();

	static Activity* _currentActivity;
	static LIST<Activity*> _startingActivities;
	static LIST<Activity*> _stoppingActivities;
	static LIST<Activity*> _backList;

	friend class EventManager;

	friend class Activity;

	friend class ardUI;
};

#endif //ARDUI_ACTIVITYMANAGER_H
