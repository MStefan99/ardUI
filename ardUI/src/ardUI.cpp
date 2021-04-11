//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


void ardUI::back() {
	ActivityManager::back();
}


void ardUI::reset() {
	ActivityManager::reset();
}


void ardUI::setViewName(View* view, const String& name) {
	ardUI::getInstance().viewMap[name] = view;
}


View* ardUI::getViewByName(const String& name) {
	return ardUI::getInstance().viewMap[name];
}
