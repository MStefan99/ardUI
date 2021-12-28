//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_ACTIVITYSWITCHER_H
#define ARDUI_ACTIVITYSWITCHER_H

#include "Activity.h"


template <class ActivityClass>
void ActivityManager::startActivity(const Bundle& extras,
		void (* onActivityResult)(int, Bundle)) {
	_startingActivities.push_back(new ActivityClass {extras, onActivityResult});
}


#endif //ARDUI_ACTIVITYSWITCHER_H
