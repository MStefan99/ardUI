//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ARDUI_HPP
#define ARDUI_ARDUI_HPP

#include "platform.hpp"
#include "EventManager.hpp"

#include "View.hpp"
#include "Bundle.hpp"
#include "Activity.hpp"
#include "ActivityManager.hpp"
#include "ActivitySwitcher.hpp"

#include LIST_H
#include MAP_H


class ardUI final {
S_PUBLIC:
	template <class ActivityClass>
	static void startActivity(const Bundle& extras = {});
	static void back();
	static void reset();

	static void setViewName(View* view, const String& name);
	static View* getViewByName(const String& name);
	static Activity* getCurrentActivity();

S_PRIVATE:
	static TL_NS::map<String, View*> _viewMap;
};


template <class ActivityClass>
void ardUI::startActivity(const Bundle& extras) {
	ActivityManager::startActivity<ActivityClass>(extras);
}


#endif //ARDUI_ARDUI_HPP
