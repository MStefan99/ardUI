//
// Created by MStefan99 on 16.6.21.
//

#ifndef ARDUI_BUILDERINTERFACE_H
#define ARDUI_BUILDERINTERFACE_H
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "View.h"
#include "Activity.h"
#include "ActivityManager.h"


class BuilderInterface {
public:
	Activity* getCurrentActivity() const {
		return ActivityManager::_currentActivity;
	}
};

using namespace emscripten;

EMSCRIPTEN_BINDINGS(BuilderInterface) {
	class_<Rect>("Rect")
			.constructor()
			.property("left", &Rect::left)
			.property("top", &Rect::top)
			.property("right", &Rect::right)
			.property("bottom", &Rect::bottom);

	class_<Drawable>("Drawable")
			.property("_viewBox", &View::_viewBox);

	class_<View, base<Drawable>>("View")
			.property("_measuredWidth", &View::_measuredWidth)
			.property("_measuredHeight", &View::_measuredHeight)
			.function("invalidate", &View::invalidate);

	class_<LIST<View*>>("list");

	class_<ViewGroup, base<View>>("ViewGroup")
			.property("_viewList", &ViewGroup::_viewList);

	class_<LinearLayout, base<ViewGroup>>("LinearLayout")
			.property("_orientation", &LinearLayout::_orientation);

	class_<Activity>("Activity")
			.function("getRootView", &Activity::getRootView,
					allow_raw_pointers());

	class_<BuilderInterface>("BuilderInterface")
			.constructor()
			.function("getCurrentActivity", &BuilderInterface::getCurrentActivity,
					allow_raw_pointers());
}


#endif
#endif //ARDUI_BUILDERINTERFACE_H
