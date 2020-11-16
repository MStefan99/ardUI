//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_H
#define ARDUI_H


#include "platform.h"
#include "llpi.h"
#include "ardUI_config.h"
#include "Singleton.h"

#include "Event.h"
#include "EventManager.h"
#include "View.h"
#include "Activity.h"
#include "ActivityManager.h"
#include "ActivitySwitcher.h"

#include LIST_H
#include MAP_H


class ardUI final: public Singleton<ardUI> {
public:
	ardUI() = default;

	template <class ActivityClass>
	void startFirstActivity();
	static void back();
	static void reset();

	void setViewName(View* view, const String& name);
	View* getViewByName(const String& name);

private:
	MAP<String, View*> viewMap;
};


template <class ActivityClass>
void ardUI::startFirstActivity() {
	if (!ActivityManager::currentActivity) {
		ActivityManager::switchActivity<ActivityClass>();
	}
}


#endif //ARDUI_H
