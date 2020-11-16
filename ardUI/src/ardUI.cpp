//
// Created by MStefan99 on 16.12.19.
//

#include "ardUI.h"


MAP<String, View*> ardUI::viewMap {};


void ardUI::setViewName(View* view, const String& name) {
	viewMap[name] = view;
}


View* ardUI::getViewByName(const String& name) {
	return viewMap[name];
}


void ardUI::back() {
	ActivityManager::back();
}


void ardUI::exit() {
	ActivityManager::exit();
}
