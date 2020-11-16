//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_H
#define ARDUI_H


#include "platform.h"
#include "llpi.h"
#include "ardUI_config.h"

#include "Event.h"
#include "EventManager.h"
#include "View.h"
#include "Activity.h"
#include "ActivityManager.h"
#include "ActivitySwitcher.h"

#include LIST_H
#include MAP_H


class ardUI final {
public:
	ardUI() = delete;

	template <class ActivityClass>
	static void startFirstActivity();
	static void back();
	static void exit();

	static void setViewName(View* view, const String& name);
	static View* getViewByName(const String& name);

private:
	static MAP<String, View*> viewMap;
};


template <class ActivityClass>
void ardUI::startFirstActivity() {
	if (!ActivityManager::currentActivity) {
		ActivityManager::switchActivity<ActivityClass>();
	}
}


#endif //ARDUI_H
