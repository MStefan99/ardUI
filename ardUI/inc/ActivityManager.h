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
	static void switchActivity(const Bundle& extras = {},
														 void (* onActivityResult)(int statusCode, Bundle resultData) = {});
	static void stopActivity(Activity* activityToStop);
	static void back();
	static void reset();

	static void cleanup();

	static Activity* currentActivity;
	static LIST<Activity*> activitiesToStop;
	static LIST<Activity*> backList;

	friend class EventManager;

	friend class Activity;

	friend class ardUI;
};

#endif //ARDUI_ACTIVITYMANAGER_H
