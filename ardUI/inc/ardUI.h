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
	template <class ActivityClass>
	static void startActivity(const Bundle& extras = {});
	static void back();
	static void reset();

	static void setViewName(View* view, const String& name);
	static View* getViewByName(const String& name);
	static Activity& getCurrentActivity();

	friend class Singleton<ardUI>;

private:
	ardUI() = default;
	~ardUI() = default;
	MAP<String, View*> _viewMap;
};


template <class ActivityClass>
void ardUI::startActivity(const Bundle& extras) {
	ActivityManager::startActivity<ActivityClass>(extras);
}


#endif //ARDUI_H
