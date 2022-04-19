//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_ACTIVITYSWITCHER_HPP
#define ARDUI_ACTIVITYSWITCHER_HPP

#include "Activity.hpp"


template <class ActivityClass>
void ActivityManager::startActivity(const Bundle& extras,
		void (* onActivityResult)(int, Bundle)) {
	_startingActivities.push_back(new ActivityClass {extras, onActivityResult});
}


#endif //ARDUI_ACTIVITYSWITCHER_HPP
