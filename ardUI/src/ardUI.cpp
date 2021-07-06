//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


ardUI::~ardUI() {
	reset();
}


void ardUI::back() {
	ActivityManager::back();
}


void ardUI::reset() {
	ActivityManager::reset();
	ActivityManager::processWaitingActivities();
}


void ardUI::setViewName(View* view, const String& name) {
	ardUI::getInstance()._viewMap[name] = view;
}


View* ardUI::getViewByName(const String& name) {
	return ardUI::getInstance()._viewMap[name];
}


Activity& ardUI::getCurrentActivity() {
	return *ActivityManager::_currentActivity;
}
