//
// Created by MStefan99 on 5.8.21.
//

#include "BuilderInterface.h"


#ifdef __EMSCRIPTEN__
Activity* BuilderInterface::getCurrentActivity() const {
	return ActivityManager::_currentActivity;
}
#endif
