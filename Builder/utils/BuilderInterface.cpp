//
// Created by MStefan99 on 5.8.21.
//

#include "BuilderInterface.h"


Activity* BuilderInterface::getCurrentActivity() const {
	return ActivityManager::_currentActivity;
}
