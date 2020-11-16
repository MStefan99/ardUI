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
	static void switchActivity(const Bundle& extras = {});
	static void back();
	static void exit();

	static Activity* currentActivity;
	static LIST<Activity*> backList;

	friend class EventManager;

	friend class ardUI;
};




#endif //ARDUI_ACTIVITYMANAGER_H
